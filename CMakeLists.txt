# How to use:
#   mkdir build
#   cd build
#   cmake ..
#   make
#
cmake_minimum_required(VERSION 3.10.2)

project(STANK
    VERSION 0.1.0)

add_executable(stank src/client.cpp)

add_executable(stank_server src/server.cpp)