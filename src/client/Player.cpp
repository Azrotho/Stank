//
// Created by azrotho on 20/10/2026.
//

#include "Player.h"
//branchez vous liste d'initialisation, ça sauve des vies à ce qu'il parait
//https://www.reddit.com/r/Cplusplus/comments/10z8e5e/what_is_the_difference_between_the_member/?tl=fr
Player::Player(float cx,float cy, float crot, std::string text) : texture(text), sprite(texture) {
    x=cx;
    y=cy;
    rot=crot;
}

void Player::deceleration(float dt) {
    if (speed>-10.0f && speed<10.0f){
        speed=0;
    }
    if (speed>0) speed-=(accel*dt)*5;
    if (speed<0) speed+=(accel*dt)*5;
}

bool Player::whatDir(){
    if(speed>=0)return true;
    return false;
}

void Player::move(bool forward,bool backward,bool right,bool left,float dt){
    bool previousDir=whatDir();
    //j'ai trouvé ceci
    //https://www.reddit.com/r/gamedev/comments/6j8ovg/acceleration_why_pos_vel_dt_vel_acc_dt/
    if(forward && !backward){
        if(speed>0){
            speed+=accel*dt;
        }else if(speed==0){
            speed=1.0f;
        }else{
            deceleration(dt);
        }
    }else if(backward && !forward){
        if(speed<0){
            speed-=accel*dt;
        }else if(speed==0){
            speed=-1.0f;
        }else{
            deceleration(dt);
        }
    }else{
        deceleration(dt);
    }
    bool currentDir=whatDir();

    //previousDir et currentDir permettent de pas juste de passer de turn=100 à turn=-100 net et c'est vachement plus sympa à jouer
    if(currentDir != previousDir) turn=0;

    if(right && !left){
        turn+=turnAccel*dt;
    }else if(left && !right) {
        turn-=turnAccel*dt;
    }else{
        turn=0;
    }

    //remise de speed à maxspeed si ça dépasse
    if (speed>maxSpeed) speed=maxSpeed;
    if (speed<-maxSpeed) speed=-maxSpeed;

    //remise de turn à maxTurn si ça dépasse
    if (turn>maxTurn) turn=maxTurn;
    if (turn<-maxTurn) turn=-maxTurn;

    //affectation de la position du tank
    float realTurn=turn;
    if(speed<0) realTurn=-realTurn;
    rot+=realTurn*dt;
    double rad = rot * (M_PI/180.0f);
    x += (float) (cos(rad)*(speed*dt));
    y += (float) (sin(rad)*(speed*dt));
    float spriteRot = (rot-90)* (M_PI/180.0f);
    setSprite(x,y,spriteRot,2.0f);
}

/******************************
/
/ GETTERS ET SETTERS
/
******************************/


float Player::getX() const{
    return x;
}

float Player::getY() const{
    return y;
}

float Player::getRotation() const{
    return rot;
}

void Player::setX(float newX){
    x=newX;
}

void Player::setY(float newY){
    y=newY;
}

void Player::setRotation(float newRotation){
    rot=newRotation;
}

float Player::getSpeed() const{
    return speed;
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