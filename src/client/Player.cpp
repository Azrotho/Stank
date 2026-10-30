//
// Created by azrotho on 20/10/2026.
//

#include "Player.h"
void Player::move(float forward, float turnTimesDT) {
    rot+=turnTimesDT*50.0f;
    double rad = rot * (M_PI/180.0f);
    x += (float) (cos(rad)*forward);
    y += (float) (sin(rad)*forward);
}