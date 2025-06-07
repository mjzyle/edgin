cmake_minimum_required(VERSION 3.10)
project(LogicUnit)

set(CMAKE_CXX_STANDARD 17)

#add_subdirectory(io)
#add_subdirectory(decoder)
#add_subdirectory(classifier)
#add_subdirectory(dj)
add_subdirectory(external/whisper.cpp)
add_subdirectory(external/libsndfile)

add_executable(logic_unit main.cpp decoder/Decoder.cpp)
target_link_libraries(logic_unit whisper)
target_link_libraries(logic_unit sndfile)