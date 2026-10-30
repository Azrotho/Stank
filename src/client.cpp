//
// Created by azrotho on 09/10/2026.
//
#include <gf/Event.h>
#include <gf/Font.h>
#include <gf/RenderWindow.h>
#include <gf/Sprite.h>
#include <gf/Text.h>
#include <gf/Texture.h>
#include <gf/Window.h>
#include <gf/Action.h>
#include <iostream>
#include <random>
#include <gf/Random.h>
#include <cmath>

#include "common/Constants.h"

#include "client/ClientNetwork.h"
#include "client/Player.h"

static float deceleration(float speed,float accel) {
    if (speed>-2.0f && speed<2.0f) speed=0;
    if (speed>0) speed-=accel;
    if (speed<0)speed+=accel;
    return speed;
}

int main() {

    //set les touches :
    gf::Action rotateLeft("RotateLeft");
    rotateLeft.setContinuous();
    rotateLeft.addScancodeKeyControl(gf::Scancode::A);
    rotateLeft.addKeycodeKeyControl(gf::Keycode::Left);

    gf::Action rotateRight("RotateRight");
    rotateRight.setContinuous();
    rotateRight.addScancodeKeyControl(gf::Scancode::D);
    rotateRight.addKeycodeKeyControl(gf::Keycode::Right);

    gf::Action moveForward("moveForward");
    moveForward.setContinuous();
    moveForward.addScancodeKeyControl(gf::Scancode::W);
    moveForward.addKeycodeKeyControl(gf::Keycode::Up);

    gf::Action moveBackward("moveBackward");
    moveBackward.setContinuous();
    moveBackward.addScancodeKeyControl(gf::Scancode::S);
    moveBackward.addKeycodeKeyControl(gf::Keycode::Down);

    gf::ActionContainer actions;
    actions.addAction(rotateLeft);
    actions.addAction(rotateRight);
    actions.addAction(moveForward);
    actions.addAction(moveBackward);

    float tickTimeAccumulator = 0.0f;

    //variables pour la vitesse
    float accel = 0.05f;
    float speed = 0.0f;
    float maxSpeed = 25.0f;
    float turn = 0.0f;
    float turnAccel=0.05f;
    float maxTurn=5.0f;

    std::cout << "Hello, World Client!" << std::endl;

    ClientNetwork networking;
    networking.start();

    Player player;

    gf::Window window("Stank", { 640, 480 });
    gf::RenderWindow renderer(window);
    renderer.clear(gf::Color::White);

    gf::Texture texture("sprite/PNG/default/barrelRed_side.png");
    gf::Sprite sprite(texture);

    gf::Font font("DroidSans.ttf");

    gf::Text text("Hello gf!", font, 50);
    text.setColor(gf::Color4f(0.0f,0.0f,0.0f,1.0f));
    text.setPosition({ 100, 100 });
    sprite.setPosition({ player.x, player.y });
    sprite.setScale(4.0f);
    sprite.setAnchor(gf::Anchor::Center);

    gf::Clock clock;

    while (window.isOpen()) {
        // Process events
        float dt = clock.restart().asSeconds();

        // Envoyer packet ClientMove tout les 30tps (1 / 30)
        tickTimeAccumulator += dt;

        gf::Event event;
        while (window.pollEvent(event)) {
            actions.processEvent(event);
            switch (event.type) {
                case gf::EventType::Closed:
                    window.close();
                    networking.stop();
                    break; // TODO: Séparé input & update
                default:
                    break;
            }
        }

        if (networking.m_isConnected.load()) {
            text.setString("Connexion OK");
        } else {
            text.setString("Connexion KO");
        }

        //déplacements
        if ((rotateRight.isActive()==false && rotateLeft.isActive()==false) || (rotateRight.isActive() && rotateLeft.isActive())){
            turn=0;
        }else {
            if ((rotateRight.isActive() && speed>=0) || (rotateLeft.isActive() && speed<0)) turn +=turnAccel;
            if ((rotateRight.isActive() && speed<0) || (rotateLeft.isActive() && speed>=0)) turn -=turnAccel;
        }
        if ((moveForward.isActive()==false && moveBackward.isActive()==false) || (moveForward.isActive() && moveBackward.isActive())){
            speed=deceleration(speed,accel);
        }else {
            if (moveForward.isActive()) speed+=accel;
            if (moveBackward.isActive()) speed-=accel;
        }
        //remise de speed à maxspeed si ça dépasse
        if (speed>maxSpeed) speed=maxSpeed;
        if (speed<-maxSpeed) speed=-maxSpeed;
        //remise de turn à maxTurn si ça dépasse
        if (turn>maxTurn) turn=maxTurn;
        if (turn<-maxTurn) turn=-maxTurn;

        player.move(speed*dt,turn*dt);
        actions.reset();

        if (tickTimeAccumulator >= (1.0f / 30.0f)) {
            //networking.send(ClientMove{player.x, player.y, player.rot});
            tickTimeAccumulator = 0.0f;
        }

        // Draw the entities
        renderer.clear();
        sprite.setPosition({ player.x, player.y });
        sprite.setRotation((float) (player.rot*(M_PI/180.0f)));
        renderer.draw(sprite);
        renderer.draw(text);
        renderer.display();
    }
    return 0;
}
