//
// Created by shirocku on 20/10/2026.
//

#ifndef STANK_SERVERNETWORKING_H
#define STANK_SERVERNETWORKING_H

#include <thread>
#include <gf/SocketSelector.h>
#include <gf/TcpListener.h>
#include <gf/Random.h>
#include <gf/Ref.h>
#include <gf/Log.h>
#include "GameState.h"


class ServerNetworking {
    public:
    ServerNetworking(gf::Random& random);
    void start();
    void stop();
    void run();
    int runClient();
    private:
    std::thread networkThread;
    gf::TcpListener m_listener;
    gf::SocketSelector m_selector;
    GameState m_gameState;
    gf::Ref<gf::Random> m_random;

};


#endif //STANK_SERVERNETWORKING_H
