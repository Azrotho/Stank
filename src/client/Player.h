//
// Created by azrotho on 20/10/2026.
//

#ifndef STANK_PLAYER_H
#define STANK_PLAYER_H

#include <cmath>

class Player {
	public:
		float x = 0;
		float y = 0;
		float rot = 0;
		void move(float forward, float turnTimesDT);
};


#endif //STANK_PLAYER_H
