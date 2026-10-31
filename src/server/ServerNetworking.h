//
// Created by shirocku on 20/10/2026.
//

#ifndef STANK_SERVERNETWORKING_H
#define STANK_SERVERNETWORKING_H

#include <thread>
#include <gf/SocketSelector.h>
#include <gf/TcpListener.h>

#include "GameState.h"


class ServerNetworking {
    public:
    ServerNetworking();
    void start();
    void stop();
    void run();
    int runClient();
    private:
    std::thread networkThread;

    gf::SocketSelector m_selector;
    GameState m_gameState;

};


#endif //STANK_SERVERNETWORKING_H
