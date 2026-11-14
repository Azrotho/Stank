#ifndef STANK_PLAYER_H
#define STANK_PLAYER_H
#include <cmath>

class TankShell {
	public:
    
		TankShell(float x, float y, float rotation,float tankDamages);

		void move(float dt);
		float getX();
		float getY();
		float getRotation();
		float getSpeed();
        float getDamages();

        void setRotation(float newRotation);
        void setX(float x);
        void setY(float y);
        void setDamages(float tankDamages);
		
	private :
		void deceleration(float dt);
		float x = 200;
		float y = 200;
		float rot = 0;

		float speed = 0.0f;
        
        float damages=0.0f;

};


#endif //STANK_PLAYER_H
