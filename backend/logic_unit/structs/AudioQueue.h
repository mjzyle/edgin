#pragma once
#include <queue>
#include <string>
#include <mutex>
#include <condition_variable>

class AudioQueue {
public:
    // Add a .wav file path to the queue
    void push(const std::string& wavFile) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(wavFile);
        cv_.notify_one();
    }

    // Get the next .wav file path from the queue (blocks if empty)
    std::string pop() {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this]{ return !queue_.empty(); });
        std::string file = queue_.front();
        queue_.pop();
        return file;
    }

private:
    std::queue<std::string> queue_;
    std::mutex mutex_;
    std::condition_variable cv_;
};