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
    //Second: initialize networking object (TODO: implement a networking object)
    //Third: create a thread for each client
    //  //Fourth: wait for clients to do something
    //  //Fifth: upon receiving an input, deserialize it and send it to the network thread
    //Sixth: send input to gameLoop
    //Seventh: get gameState/answer from gameLoop
    //  //Eighth: send gameState to each client, then go to step Four
    //End of the game : disconnect from client, close port, close server
}