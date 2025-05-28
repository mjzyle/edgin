#pragma once
#include <string>

class Decoder {
public:
    Decoder();
    ~Decoder();

    // Converts audio data to text using Whisper.cpp
    std::string decodeAudio(const std::string& audioData);
};