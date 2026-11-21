#ifndef STANK_PLAYER_H
#define STANK_PLAYER_H
#include <cmath>
#include <gf/Sprite.h>
#include <gf/Texture.h>

class TankShell {
	public:
		TankShell(float x, float y, float rotation,float tankDamages,int newIdOwner);

		void move(float dt);

		float getX() const;
		float getY() const;
		float getRotation() const;
		float getSpeed() const;
        float getDamages() const;

        void setRotation(float newRotation);
        void setX(float newX);
        void setY(float newY);
        void setDamages(float tankDamages);

		void toDestroy();
		bool isDestructible() const;

	private :
		void setSprite(float posX, float posY, float rad,float scale);

		int idOwner;

		float x = 200;
		float y = 200;
		float rot = 0;

		float speed = 0.0f;
        
        float damages=0.0f;
		float distanceToMake=100.0f;
		float distanceMade=0.0f;

		gf::Texture texture;
		gf::Sprite sprite;

		bool destroyMePlease=false;
};


#endif //STANK_PLAYER_H
