//
// Created by shirocku on 20/10/2026.
//

#include "ServerNetworking.h"

#include <stdexcept>
#include <thread>

#include "../../gf/include/gf/TcpListener.h"
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
    for (;;) {
        //Second : let clients connect
        gf::TcpSocket client = listener.accept();
        if (client) {
            //Third: wait for clients to do something

        }
        //  //Fourth: upon receiving an input, deserialize it and send it to the network thread
        //Fifth: send input to gameLoop
        //Sixth: get gameState/answer from gameLoop
        //  //Seventh: send gameState to each client
    }

    stop();
}

void ServerNetworking::stop() {
    //End of the game : disconnect from client, close port, close server
}

int ServerNetworking::runClient() {
    return 0;
}