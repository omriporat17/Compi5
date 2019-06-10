cmake_minimum_required(VERSION 3.9)
project(Compi5)

set(CMAKE_CXX_STANDARD 98)

add_executable(Compi5 main.cpp output.cpp output.hpp symbolTable.cpp symbolTable.hpp StackStruct.hpp bp.cpp bp.hpp Pair.cpp Pair.hpp Registers.cpp Registers.hpp hw5.hpp hw5.cpp)