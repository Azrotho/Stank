//
// Created by shirocku on 01/11/2026.
//

#ifndef STANK_SERVERPLAYER_H
#define STANK_SERVERPLAYER_H

#include <cstdint>
#include <string>

#include <gf/Packet.h>
#include <gf/TcpSocket.h>

struct ServerPlayer {
    gf::Id id = gf::InvalidId;
    std::string name;
    gf::TcpSocket socket;
    //si besoin d'une team : int32_t team = -1;
    //si besoin d'un lobby i guess ??? : bool ready = false;

    template<typename T>
    void send(const T& data) {
        gf::Packet packet;
        packet.is(data);
        socket.sendPacket(packet);
    }
};


#endif //STANK_SERVERPLAYER_H
