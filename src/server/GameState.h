//
// Created by shirocku on 21/10/2026.
//

#ifndef STANK_GAMESTATE_H
#define STANK_GAMESTATE_H

#include "serverPlayer.h"

class GameState {
    public:
    GameState();
    void update(ServerPlayer player, gf::Packet packet);
    private:

};

#endif //STANK_GAMESTATE_H
