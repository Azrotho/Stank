# How to use:
#   mkdir build
#   cd build
#   cmake ..
#   make
#
cmake_minimum_required(VERSION 3.22)

project(STANK
    VERSION 0.1.0)

add_executable(stank src/client.cpp
        src/client/ClientNetwork.h
        src/common/Constants.h
        src/client/ClientNetwork.cpp
        src/client/Player.h
        src/client/Player.cpp
        src/common/Protocol.h)


add_subdirectory(vendor/box2d)


find_package(gf 1.2.0 REQUIRED COMPONENTS graphics net)
#find_package(box2d 3.2.0 REQUIRED)


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
        src/server/ServerNetworking.cpp
        src/server/ServerNetworking.h
        src/server/GameState.cpp
        src/server/GameState.h
        src/server/ServerEntity.cpp
        src/server/ServerEntity.h
        src/common/Protocol.h
        src/server/ServerUtility.cpp
        src/server/ServerUtility.h
        src/server/ServerPlayer.cpp
        src/server/ServerPlayer.h
        src/server/ServerLobby.cpp
        src/server/ServerLobby.h
)

target_link_libraries(stank_server
        PUBLIC
        box2d::box2d
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