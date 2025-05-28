cmake_minimum_required(VERSION 3.10)
project(LogicUnit)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(io)
add_subdirectory(decoder)
add_subdirectory(classifier)
add_subdirectory(dj)

add_executable(logic_unit main.cpp)
target_link_libraries(logic_unit IOHandler Decoder Classifier DJ)