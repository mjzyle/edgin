#pragma once
#include <string>

class Classifier {
public:
    Classifier();
    ~Classifier();

    // Classifies text using an AI/ML model
    std::string classifyText(const std::string& text);
};