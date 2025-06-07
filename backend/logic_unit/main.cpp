//#include "io/IOHandler.h"
#include "decoder/Decoder.h"
//#include "classifier/Classifier.h"
//#include "dj/DJ.h"
#include <iostream>
#include <thread>

int main() {
    //IOHandler ioHandler;
    //Classifier classifier;
    //DJ dj;

    AudioQueue audioQueue;

    Decoder decoder(audioQueue);

    // Start up components
    std::thread threadDecoder([&decoder]() {
        decoder.processLoop();
    });

    // TEST DECODER
    audioQueue.push("/workspaces/edgin/backend/logic_unit/external/whisper.cpp/samples/jfk.wav");
    audioQueue.push("/workspaces/edgin/backend/logic_unit/external/whisper.cpp/samples/jfk2.wav");
    audioQueue.push("/workspaces/edgin/backend/logic_unit/external/whisper.cpp/samples/jfk3.wav");

    // Control loop
    while (true) {
        // Here you can add logic to control the flow of the program
        // For example, you could check for user input or other conditions
        // to break out of the loop and terminate the program gracefully.
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate work
    }

    // Wait for components to finish
    threadDecoder.join();
    std::cout << "Terminated: Decoder" << std::endl;

    return 0;
}