//
// Created by azrotho on 20/10/2026.
//

#ifndef STANK_PLAYER_H
#define STANK_PLAYER_H

#include <gf/Sprite.h>
#include <gf/Texture.h>
#include <string>
#include <cmath>

class Player {
	public:
		//Create a player instance with coordinates (x, y) , orientation rot and a texture path "texturePath"
		Player(float x, float y, float rot, const std::string& texturePath);

		//returns coordinate x
		float getX() const;
		//returns coordinate y
		float getY() const;
		//returns orientation (still needs conversion in radiant before usage)
		float getOrientation() const;


		//returns a the associated sprite
		gf::Sprite getSprite();
		//sets coordinates x to newX
		void setX(float newX);
		//sets coordinate y to newY
		void setY(float newY);
		//sets tank orientation in float
		void setOrientation(float newOrientation);
		//sets the sprite to position (posX, posY), with orientation in radiant rad, and of size scale
		void setSprite(float posX, float posY,float rad, float scale);

		
	private :
		float m_coordX;
		float m_coordY;
		float m_orientation;

		gf::Texture texture;
    	gf::Sprite sprite;

};


#endif //STANK_PLAYER_H
