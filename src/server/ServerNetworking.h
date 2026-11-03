//
// Created by shirocku on 20/10/2026.
//

#ifndef STANK_SERVERNETWORKING_H
#define STANK_SERVERNETWORKING_H

#include <gf/SocketSelector.h>
#include <gf/TcpListener.h>
#include <gf/Random.h>
#include <gf/Ref.h>
#include "GameState.h"
#include <atomic>
#include "ServerLobby.h"


class ServerNetworking {
    public:
    ServerNetworking(gf::Random& random);
    void run();

    private:
    static void signalHandler(int sig);


    private:
    gf::Ref<gf::Random> m_random;
    gf::TcpListener m_listener;
    gf::SocketSelector m_selector;
    ServerLobby m_lobby;
    std::map<gf::Id, ServerPlayer> m_players;
    static std::atomic_bool g_running;

};


#endif //STANK_SERVERNETWORKING_H
