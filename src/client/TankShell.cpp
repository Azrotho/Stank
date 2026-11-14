//
// Created by artaxe on 14/11/2026.
//

#include "TankShell.h"

#include <gf/Transform.h>
//branchez vous liste d'initialisation, ça sauve des vies à ce qu'il parait
//https://www.reddit.com/r/Cplusplus/comments/10z8e5e/what_is_the_difference_between_the_member/?tl=fr
TankShell::TankShell(float cx,float cy, float crot, float damage){
    setX(cx);
    setY(cy);
    setRotation(crot);
    setDamages(damage);
}


void TankShell::move(float dt) {
    speed+=dt;
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

float TankShell::getX() const{ return x;}
float TankShell::getY() const {return y;};
float TankShell::getRotation() const{return rot;};
float TankShell::getSpeed() const{return speed;};
float TankShell::getDamages() const{return damages;};
