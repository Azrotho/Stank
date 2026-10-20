# How to use:
#   mkdir build
#   cd build
#   cmake ..
#   make
#
cmake_minimum_required(VERSION 3.10.2)

project(STANK
    VERSION 0.1.0)

add_executable(stank src/client.cpp
        src/client/ClientNetwork.h
        src/common/Constants.h
        src/client/ClientNetwork.cpp
        src/client/Player.h
        src/client/Player.cpp)

find_package(gf 1.2.0 REQUIRED COMPONENTS graphics net)


target_link_libraries(stank
    PRIVATE
    gf::graphics
    gf::net
)

target_compile_options(stank
        PRIVATE
        "-Wall" "-Wextra" "-pedantic" "-g" "-O2"
)

set_target_properties(stank
        PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
)

add_executable(stank_server
        src/server.cpp
        src/common/Constants.h
    )

target_link_libraries(stank_server
        PRIVATE
        gf::net
)

target_compile_options(stank_server
        PRIVATE
        "-Wall" "-Wextra" "-pedantic" "-g" "-O2"
)

set_target_properties(stank_server
        PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
)

add_custom_command(TARGET stank POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/data/stank"
        "$<TARGET_FILE_DIR:stank>/"
)