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

#endif //STANK_STRUCT_H
