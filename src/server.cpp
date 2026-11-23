//
// Created by azrotho on 09/10/2026.
//

#include <iostream>
#include <thread>
#include "server/ServerNetworking.h"
#include "common/Constants.h"
#include <box2d/box2d.h>
#include <gf/Clock.h>
#include <gf/Log.h>

#include "common/Protocol.h"

int receive(){
    return 0;
}

int send(){
    return 0;
}


int gameLoop(ServerNetworking &networking){
    //First: Initialize the game
    gf::Clock clock;
    //Second: start a 30 TPS loop
    while (true) {
        float dt = clock.restart().asSeconds();

        std::pair<gf::Id, gf::Packet> pocketPair;
        while (networking.queue.poll(pocketPair)) {
            auto& [id, packet] = pocketPair;
            ServerPlayer &player = networking.m_players.at(id);
            switch (packet.getType()) {
                case ClientHello::type:
                    gf::Log::info(("Player " +  player.name + " say hello!\n").c_str());
                    break;
                case ClientMove::type: {
                    auto clientMove = packet.as<ClientMove>();
                    TankControls ctrl = clientMove.controls;
                    // TODO: do something with the clientMove data
                    gf::Log::info(("Player " +  player.name + " sent a ClientMove packet\n").c_str());
                    player.move(ctrl.forward, ctrl.backward,ctrl.right, ctrl.left, dt);

                    //send update ici (temporaire)
                    ServerTankUpdate update;
                    update.id = player.id;
                    update.x = player.getX();
                    update.y = player.getY();
                    update.rot = player.getRotation();
                    player.send(update);

                    break;
                }
                default:
                    gf::Log::info(("Player " +  player.name + " sent a packet of an unknowed type\n").c_str());
                    break;
            }
        }
        usleep((unsigned int) ((TICK_TIME - clock.getElapsedTime().asSeconds()) * 1000.0f));
    }
    //Third: wait for inputs from network threads
    //Fourth: modify gameState according to the inputs
    //Fifth: send gameState to the network thread then go to third step
    return 0;
}

int main() {
    //std::thread mainThread (gameLoop);
    gf::Random random = gf::Random();
    ServerNetworking networking = ServerNetworking(random);

    std::thread networkingThread(&ServerNetworking::run, &networking);

    gameLoop(networking);

    networkingThread.join();
    std::cout << "Hello, World Server!" << std::endl;

    return 0;
}