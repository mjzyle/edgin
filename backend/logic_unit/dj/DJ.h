#pragma once
#include <string>

class DJ {
public:
    DJ();
    ~DJ();

    // Generates output signals and manages playlists via Spotify API
    void process(const std::string& classification, const std::string& timingData);
};