//
// Created by shirocku on 20/10/2026.
//

#ifndef STANK_SERVERNETWORKING_H
#define STANK_SERVERNETWORKING_H

#include <thread>


class ServerNetworking {
    public:
    ServerNetworking();
    void start();
    void stop();
    void run();
    int openPort();
    int runClient();
    private:
    std::thread networkThread;
};


#endif //STANK_SERVERNETWORKING_H
