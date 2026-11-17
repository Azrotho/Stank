//
// Created by azrotho on 17/11/2026.
//

#ifndef STANK_STRUCT_H
#define STANK_STRUCT_H
#include "Enums.h"

struct TankControls {
	Direction direction = Direction::Neutral;
	Movement movement = Movement::Neutral;
	Action action = Action::Neutral;
};

template<typename Archive>
Archive& operator|(Archive& ar, TankControls& data) {
	return ar | data.direction | data.movement | data.action;
}

#endif //STANK_STRUCT_H
