//
// Created by shirocku on 20/10/2026.
//

#include "ServerNetworking.h"

#include <stdexcept>
#include <thread>

#include "../../gf/include/gf/TcpListener.h"
#include "../common/Constants.h"

ServerNetworking::ServerNetworking(gf::Random& random)
: m_random(random)
, m_listener(Service)
{
    if (!m_listener) {
        throw std::runtime_error("Can not start listener.");
    }
    m_selector.addSocket(m_listener);
    gf::Log::info("(SERVER) Waiting for connections on port %s...\n", Service);
}

void ServerNetworking::run() {
    while (g_running){
        gf::TcpSocket client = m_listener.accept();
        if (client) {
            //Third: wait for clients to do something

        }
        //  //Fourth: upon receiving an input, deserialize it and send it to the network thread
        //Fifth: send input to gameLoop
        //Sixth: get gameState/answer from gameLoop
        //  //Seventh: send gameState to each client
    }
}

