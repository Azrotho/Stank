//
// Created by artaxe on 14/11/2026.
//

#include "TankShell.h"
#include "../common/Constants.h"

#include <gf/Transform.h>
//branchez vous liste d'initialisation, ça sauve des vies à ce qu'il parait
//https://www.reddit.com/r/Cplusplus/comments/10z8e5e/what_is_the_difference_between_the_member/?tl=fr
TankShell::TankShell(float cx,float cy, float crot, float damage,int newIdOwner): texture("sprite/PNG/Retina/shotThin.png"), sprite(texture){
    setX(cx);
    setY(cy);
    setRotation(crot);
    setDamages(damage);
    idOwner = newIdOwner;
}


void TankShell::move(float dt) {
    if (distanceToMake==(distanceMade+(speed*dt))) toDestroy();
    double rad = rot * (M_PI/REVERSE_ROTATION);
    x+= (float) (cos(rad)*(speed*dt));
    y+= (float) (sin(rad)*(speed*dt));
    float spriteRot = (rot-90)* (M_PI/REVERSE_ROTATION);
    setSprite(x,y,spriteRot,2.0f);
    distanceMade+=speed*dt;
}

void TankShell::toDestroy() {
    destroyMePlease=true;
}

bool TankShell::isDestructible() const {
    return destroyMePlease;
}

/******************************
/
/ GETTERS ET SETTERS
/
******************************/

void TankShell::setX(float newX){x=newX;}
void TankShell::setY(float newY){y=newY;}
void TankShell::setRotation(float newRotation){rot=newRotation;}
void TankShell::setDamages(float tankDamages){damages=tankDamages;}

void TankShell::setSprite(float posX,float posY, float rad, float scale){
    sprite.setPosition({posX,posY});
    sprite.setScale(scale);
    sprite.setRotation(rad);
    sprite.setAnchor(gf::Anchor::Center);
}

float TankShell::getX() const{ return x;}
float TankShell::getY() const {return y;};
float TankShell::getRotation() const{return rot;};
float TankShell::getSpeed() const{return speed;};
float TankShell::getDamages() const{return damages;};