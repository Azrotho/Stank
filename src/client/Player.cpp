//
// Created by azrotho on 20/10/2026.
//

#include "Player.h"

#include "../common/Constants.h"

//branchez vous liste d'initialisation, ça sauve des vies à ce qu'il parait
//https://www.reddit.com/r/Cplusplus/comments/10z8e5e/what_is_the_difference_between_the_member/?tl=fr
Player::Player(float x,float y, float orientation, const std::string& texturePath) : texture(texturePath), sprite(texture) {
    this->m_coordX = x;
    this->m_coordY = y;
    this->m_orientation = orientation;
}

/******************************
/
/ GETTERS ET SETTERS
/
******************************/


float Player::getX() const{
    return m_coordX;
}

float Player::getY() const{
    return m_coordY;
}

float Player::getOrientation() const{
    return m_orientation;
}

void Player::setX(float newX){
    m_coordX=newX;
}

void Player::setY(float newY){
    m_coordY=newY;
}

void Player::setOrientation(float newOrientation){
    m_orientation=newOrientation;
}


void Player::setSprite(float posX,float posY, float rad, float scale){
    sprite.setPosition({posX,posY});
    sprite.setScale(scale);
    sprite.setRotation(rad);
    sprite.setAnchor(gf::Anchor::Center);
}

gf::Sprite Player::getSprite(){
    return sprite;
}