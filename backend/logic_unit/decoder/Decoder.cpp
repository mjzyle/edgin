#include "Decoder.h"
#include "whisper.h"
#include "sndfile.h"
#include <vector>
#include <cstring>
#include <iostream>

Decoder::Decoder(AudioQueue &audioQueue) : audioQueue_(audioQueue) {
    whisperContextParams_ = whisper_context_default_params();
    whisperContext_ = whisper_init_from_file_with_params(
        "/workspaces/edgin/backend/logic_unit/external/whisper.cpp/models/ggml-base.en.bin"
        ,whisperContextParams_
    );
    if (!whisperContext_) {
        std::cerr << "Failed to initialize Whisper context." << std::endl;
        throw std::runtime_error("Whisper initialization failed");
    }
    whisperParams_ = whisper_full_default_params(WHISPER_SAMPLING_GREEDY);
    whisperParams_.n_threads = 4; // Set number of threads for decoding
}

Decoder::~Decoder() {
    whisper_free(whisperContext_);
    std::cout << "Decoder destroyed." << std::endl;
}

std::vector<float> Decoder::readAudioFile_(const std::string& filePath) {
    // Read the .wav audio file and return its content as a string
    std::cout << "Reading audio file: " << filePath << std::endl;
    std::vector<float> audioData;

    SF_INFO sfInfo;
    SNDFILE *file = sf_open(filePath.c_str(), SFM_READ, &sfInfo);
    if (!file) {
        std::cerr << "Failed to open audio file: " << filePath << std::endl;
        return audioData; // Return empty vector on failure
    }
    audioData.resize(sfInfo.frames * sfInfo.channels);
    sf_count_t numFramesRead = sf_readf_float(file, audioData.data(), sfInfo.frames);
    if (numFramesRead < 0) {
        std::cerr << "Error reading audio data from file: " << filePath << std::endl;
        sf_close(file);
        return audioData; // Return empty vector on failure
    }
    sf_close(file);
    std::cout << "Read " << numFramesRead << " frames from audio file." << std::endl;

    return audioData;
}

std::string Decoder::decodeAudio_(const std::vector<float> audioData) {
    std::string decodedText;

    // Decode the audio data and return the transcribed text
    std::cout << "Decoding audio data..." << std::endl;

    if (whisper_full(whisperContext_, whisperParams_, audioData.data(), audioData.size()) != 0) {
        std::cerr << "Failed to decode audio data." << std::endl;
        return ""; // Return empty string on failure
    }

    const int nSegments = whisper_full_n_segments(whisperContext_);
    if (nSegments == 0) {
        std::cerr << "No segments found in audio data." << std::endl;
        return ""; // Return empty string if no segments
    }
    for (int i = 0; i < nSegments; ++i) {
        const char *text = whisper_full_get_segment_text(whisperContext_, i);
        decodedText += text;
    }

    return decodedText;
}

void Decoder::processLoop() {
    while(true) {
        // Fetch audio data from AudioQueue
        // Decode audio data
        // Place decoded audio data in TextQueue
        std::string audioFile = audioQueue_.pop();
        std::cout << "Decoder received: " << audioFile << std::endl;
        std::vector<float> audioData = readAudioFile_(audioFile);
        if (audioData.empty()) {
            std::cerr << "No audio data to decode." << std::endl;
            continue; // Skip if no audio data
        }
        std::string decodedText = decodeAudio_(audioData);
        std::cout << "Decoded text: " << decodedText << std::endl;
    }
}