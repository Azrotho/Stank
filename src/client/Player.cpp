//
// Created by azrotho on 20/10/2026.
//

#include "Player.h"

void Player::deceleration(float dt) {
    if (speed>-2.0f && speed<2.0f) speed=0;
    if (speed>0) speed-=(accel*dt)*5;
    if (speed<0) speed+=(accel*dt)*5;
}

void Player::move(bool forward,bool backward,bool right,bool left,float dt){
    //j'ai trouvé ceci
    //https://www.reddit.com/r/gamedev/comments/6j8ovg/acceleration_why_pos_vel_dt_vel_acc_dt/
    if(forward && !backward){
        if(speed>0){
            speed+=accel*dt;
        }else if(speed==0){
            speed=1.0f;
        }else{
            speed=0;
        }
    }else if(backward && !forward){
        if(speed<0){
            speed-=accel*dt;
        }else if(speed==0){
            speed=-1.0f;
        }else{
            speed=0;
        }
    }else{
        deceleration(dt);
    }

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
}

/******************************
/
/ GETTERS ET SETTERS
/
******************************/


float Player::getX(){
    return x;
}

float Player::getY(){
    return y;
}

float Player::getRotation(){
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

float Player::getSpeed(){
    return speed;
}