#ifndef STANK_TANKSHELL_H
#define STANK_TANKSHELL_H
#include <cmath>
#include <gf/Sprite.h>
#include <gf/Texture.h>
#include <box2d/box2d.h>

class ServerTankShell {
	public:
		ServerTankShell(float x, float y, float rotation,float tankDamages,int newIdOwner);

		bool move(float dt);

		float getX() const;
		float getY() const;
		float getRotation() const;
		float getSpeed() const;
        float getDamages() const;

        void setRotation(float newRotation);
        void setX(float newX);
        void setY(float newY);
        void setDamages(float tankDamages);


	private :

		int idOwner;

		float x = 200;
		float y = 200;
		float rot = 0;

		float speed = 0.0f;
        
        float damages=0.0f;
		float distanceToMake=100.0f;
		float distanceMade=0.0f;

		

		bool destroyMePlease=false;
};


#endif //STANK_TANKSHELL_H
