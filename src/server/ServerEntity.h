//
// Created by shirocku on 21/10/2026.
//

#ifndef STANK_SERVERENTITY_H
#define STANK_SERVERENTITY_H
#include <cstdint>


class ServerEntity {
    public:
    ServerEntity();
    private:
    uint32_t id;
    float posX, posY;
};


#endif //STANK_SERVERENTITY_H
