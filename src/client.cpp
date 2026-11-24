//
// Created by azrotho on 09/10/2026.
//
#include <cinttypes>
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

    gf::Action shoot("shoot");
    shoot.setContinuous();
    shoot.addScancodeKeyControl(gf::Scancode::Space);


    gf::ActionContainer actions;
    actions.addAction(rotateLeft);
    actions.addAction(rotateRight);
    actions.addAction(moveForward);
    actions.addAction(moveBackward);
    actions.addAction(shoot);


    float tickTimeAccumulator = 0.0f;

    std::cout << "Hello, World Client!" << std::endl;

    ClientNetwork networking;
    networking.start();

    gf::Window window("Stank", { 640, 480 });
    gf::RenderWindow renderer(window);
    renderer.clear(gf::Color::White);

    Player player(200,200,0, "sprite/PNG/default/tank_red.png");

    gf::Font font("DroidSans.ttf");

    gf::Text text("Hello gf!", font, 50);
    text.setColor(gf::Color4f(0.0f,0.0f,0.0f,1.0f));
    text.setPosition({ 100, 100 });

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
                    break; // TODO: Séparer input & update
                default:
                    break;
            }
        }

        if (networking.m_isConnected.load()) {
            text.setString("Connexion OK");
        } else {
            text.setString("Connexion KO");
        }

        if (tickTimeAccumulator >= TICK_TIME) {
            if (networking.m_isConnected.load()) {
                gf::Packet packet;
                while (networking.queue.poll(packet)) {
                    switch (packet.getType()) {
                        case ServerHello::type: {
                            ServerHello serverHello;
                            serverHello = packet.as<ServerHello>();
                            gf::Log::info("Received ServerHello packet from server my name is %s", serverHello.name.c_str());
                            break;
                        }
                        case ServerTankUpdate::type: {
                            ServerTankUpdate serverTankUpdate;
                            serverTankUpdate = packet.as<ServerTankUpdate>();
                            player.setX(serverTankUpdate.x);
                            player.setY(serverTankUpdate.y);
                            player.setOrientation(serverTankUpdate.rot);
                            gf::Log::info("Received ServerTankUpdate packet X=%f Y=%f ROT=%f \n", serverTankUpdate.x, serverTankUpdate.y, serverTankUpdate.rot);
                            break;
                        }
                        default:
                            gf::Log::info("Received packet of unknown type from server\n");
                            break;
                    }
                }


                TankControls controls;
                controls.forward = moveForward.isActive();
                controls.backward = moveBackward.isActive();
                controls.left = rotateLeft.isActive();
                controls.right = rotateRight.isActive();
                controls.action = shoot.isActive() ? Action::Shoot : Action::Neutral; 
                networking.send(ClientMove{controls});
            }
            tickTimeAccumulator = 0.0f;
        }

        actions.reset();

        // Draw the entities
        renderer.clear();
        float spriteRot = (player.getOrientation()-90.0f)* (M_PI/180.0f);
        player.setSprite(player.getX(),player.getY(),spriteRot,2.0f);
        gf::Sprite s = player.getSprite();
        renderer.draw(s);
        renderer.draw(text);
        renderer.display();
    }
    return 0;
}
