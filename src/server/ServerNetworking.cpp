//
// Created by shirocku on 20/10/2026.
//

#include "ServerNetworking.h"

#include <iostream>
#include <stdexcept>
#include <thread>

#include "serverPlayer.h"
#include "../common/Constants.h"

ServerNetworking::ServerNetworking() = default;

void ServerNetworking::start() {
    networkThread = std::thread(&ServerNetworking::run, this);
}

void ServerNetworking::run() {
    //First: Create TCPListener
    std::string port = SERVER_PORT;
    gf::TcpListener listener(port);
    if (!listener) {
        throw std::runtime_error("Can not start listener");
    }
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

        if (m_selector.isReady(listener)){
        gf::TcpSocket socket = listener.accept();

        if (!socket){
            continue;
        }
        

    }

    stop();
}

void ServerNetworking::stop() {
    //End of the game : disconnect from client, close port, close server
}

int ServerNetworking::runClient() {
    return 0;
}