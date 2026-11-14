//
// Created by azrotho on 20/10/2026.
//

#ifndef STANK_PLAYER_H
#define STANK_PLAYER_H

#include <gf/Sprite.h>
#include <gf/Texture.h>
#include <cmath>

class Player {
	public:
		void move(bool forward,bool backward,bool right,bool left,float dt);
		//renvoie true si un obus a été créé
		//renvoie false sinon
		bool shoot(); // pas encore implem
		float getX();
		float getY();
		float getRotation();
		float getSpeed();

		void setX(float newX);
		void setY(float newY);
		void setRotation(float newRotation);
		
	private :
		void deceleration(float dt);
		bool whatDir();
		float x = 200;
		float y = 200;
		float rot = 0;
		//variables pour la vitesse
		float accel = 70.0f;
		float speed = 0.0f;
		float maxSpeed = 100.0f;
		//variables pour tourner
		float turn = 0.0f;
		float turnAccel=300.0f;
		float maxTurn=150.0f;
		//frein
		float brake=200.0f;

		//stats de bases
		float pv=100.0f;
		float pvMax=100.0f;
		float damages=50.0f;
	    float reloadTime=3.0f;


		gf::Texture texture;
    	gf::Sprite sprite;
};


#endif //STANK_PLAYER_H
