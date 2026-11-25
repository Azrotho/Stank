//
// Created by artaxe on 14/11/2026.
//

#include "ServerTankShell.h"
#include <gf/Transform.h>
//branchez vous liste d'initialisation, ça sauve des vies à ce qu'il parait
//https://www.reddit.com/r/Cplusplus/comments/10z8e5e/what_is_the_difference_between_the_member/?tl=fr
ServerTankShell::ServerTankShell(float cx,float cy, float crot, float damage,int newIdOwner){
    setX(cx);
    setY(cy);
    setRotation(crot);
    setDamages(damage);
    idOwner = newIdOwner;
    gf::Texture text("sprite/PNG/Retina/shotThin.png");
    gf::Sprite sprite(text);
    
}

bool ServerTankShell::move(float dt) {
    if (distanceToMake==(distanceMade+(speed*dt))) destroyMePlease=true;
    double rad = rot * (M_PI/180.0f);
    x+= (float) (cos(rad)*(speed*dt));
    y+= (float) (sin(rad)*(speed*dt));
    float spriteRot = (rot-90)* (M_PI/180.0f);
    distanceMade+=speed*dt;
    return destroyMePlease;
}

/******************************
/
/ GETTERS ET SETTERS
/
******************************/

void ServerTankShell::setX(float newX){x=newX;}
void ServerTankShell::setY(float newY){y=newY;}
void ServerTankShell::setRotation(float newRotation){rot=newRotation;}
void ServerTankShell::setDamages(float tankDamages){damages=tankDamages;}

float ServerTankShell::getX() const{ return x;}
float ServerTankShell::getY() const {return y;}
float ServerTankShell::getRotation() const{return rot;}
float ServerTankShell::getSpeed() const{return speed;}
float ServerTankShell::getDamages() const{return damages;}