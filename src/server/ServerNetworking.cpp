//
// Created by shirocku on 20/10/2026.
//

#include "ServerNetworking.h"

#include <iostream>
#include <stdexcept>
#include <thread>

#include "serverPlayer.h"
#include "../common/Constants.h"

ServerNetworking::ServerNetworking(gf::Random& random)
:m_random(random)
,m_listener(Service)
{
    if (!m_listener) {
        throw std::runtime_error("Can not start listener");
    }
    m_selector.addSocket(m_listener);

    gf::Log::info("(SERVER) Waiting for connections on port %s...\n", Service);
}

void ServerNetworking::start() {
    networkThread = std::thread(&ServerNetworking::run, this);
}

void ServerNetworking::run() {
    //TODO : This player is temporary, we'll need to modify this
    ServerPlayer player;
    bool needsDisconnection = false;
    for (;;) {

        //On répète cette boucle pour chaque joueur jusqu'à ///
        if (m_selector.isReady(player.socket)) {
            gf::Packet packet;

            switch (player.socket.recvPacket(packet)) {
                case gf::SocketStatus::Data:
                    switch (packet.getType()) {
                        /*case ClientDisconnect::type:
                            needsDisconnection = true;
                            break; //Pas compris où trouver ceci*/
                        default:
                            m_gameState.update(std::move(player), packet);
                    }
                    break;
                case gf::SocketStatus::Error:
                    break;
                case gf::SocketStatus::Close:
                    needsDisconnection = true;
                    break;
                case gf::SocketStatus::Block:
                    break;
            }
        }
        //Jusqu'ici

        if (m_selector.isReady(m_listener)) {
            gf::TcpSocket socket = m_listener.accept();

            if (!socket){
                continue;
            }

            gf::Id id = m_random.get().computeId();
            ServerPlayer playerInstance;
            playerInstance.id = id;
            playerInstance.name = "";
            playerInstance.socket = std::move(socket);

            m_selector.addSocket(playerInstance.socket);

        }



    }

    stop();
}

/*
void ServerNetworking::stop() {
    //End of the game : disconnect from client, close port, close server
}

int ServerNetworking::runClient() {
    return 0;
}*/