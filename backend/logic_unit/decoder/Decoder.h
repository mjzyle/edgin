#pragma once
#include <string>
#include "../structs/AudioQueue.h"
#include "whisper.h"

class Decoder {
public:
    Decoder(AudioQueue &audioQueue);
    ~Decoder();

    void processLoop();

private:
    AudioQueue &audioQueue_;
    struct whisper_context *whisperContext_;
    struct whisper_full_params whisperParams_;
    struct whisper_context_params whisperContextParams_;
    std::vector<float> readAudioFile_(const std::string& filePath);
    std::string decodeAudio_(const std::vector<float> audioData);
};