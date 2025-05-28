#pragma once
#include <string>

class IOHandler {
public:
    IOHandler();
    ~IOHandler();

    // Receives audio data from web API
    std::string receiveAudio();

    // Sends output signals to web API
    void sendOutput(const std::string& output);
};