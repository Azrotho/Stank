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

    std::cout << "Hello, World Client!" << std::endl;

    ClientNetwork networking;
    networking.start();

    Player player;

    gf::Window window("Stank", { 640, 480 });
    gf::RenderWindow renderer(window);
    renderer.clear(gf::Color::White);

    gf::Texture texture("sprite/PNG/default/tank_red.png");
    gf::Sprite sprite(texture);

    gf::Font font("DroidSans.ttf");

    gf::Text text("Hello gf!", font, 50);
    text.setColor(gf::Color4f(0.0f,0.0f,0.0f,1.0f));
    text.setPosition({ 100, 100 });
    sprite.setPosition({ player.getX(), player.getY() });
    sprite.setScale(2.0f);
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
        player.move(moveForward.isActive(),moveBackward.isActive(),rotateRight.isActive(),rotateLeft.isActive(),dt);
        actions.reset();

        if (tickTimeAccumulator >= (1.0f / 30.0f)) {
            if (networking.m_isConnected.load()) {
                networking.send(ClientMove{player.getX(), player.getY(), player.getRotation()});
            }
            tickTimeAccumulator = 0.0f;
        }

        // Draw the entities
        renderer.clear();
        sprite.setPosition({ player.getX(), player.getY() });
        sprite.setRotation((float) ((player.getRotation()-90)*(M_PI/180.0f)));
        renderer.draw(sprite);
        renderer.draw(text);
        renderer.display();
    }
    return 0;
}
