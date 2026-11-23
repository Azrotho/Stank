//
// Created by azrotho on 17/11/2026.
//

#ifndef STANK_STRUCT_H
#define STANK_STRUCT_H
#include "Enums.h"

struct TankControls {
	bool forward=false;
	bool backward=false;
	bool right=false;
	bool left=false;
	Action action = Action::Neutral;
};

template<typename Archive>
Archive& operator|(Archive& ar, TankControls& data) {
	return ar | data.forward | data.backward | data.right | data.left | data.action;
}

#endif //STANK_STRUCT_H
