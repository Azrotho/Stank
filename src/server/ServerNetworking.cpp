//
// Created by shirocku on 20/10/2026.
//

#include "ServerNetworking.h"

#include <thread>

ServerNetworking::ServerNetworking() = default;

void ServerNetworking::start() {
    networkThread = std::thread(&ServerNetworking::run, this);
}

void ServerNetworking::run() {
    //First: open port to let clients connect
    int retPort = openPort();
    if (retPort != 0) {
        //erreur : à préciser
    }
    //once clients connected :
    int nbClients = 1;//TODO
    //Second: create a thread for each client
    for (int i = 0 ; i < nbClients ; i++) {

    }
    while (true) {
        //  //Third: wait for clients to do something
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

int ServerNetworking::openPort() {
    return 0;
}

int ServerNetworking::runClient() {
    return 0;
}