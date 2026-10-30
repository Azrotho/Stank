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
#include <iostream>
#include <random>
#include <gf/Random.h>

#include "common/Constants.h"

#include "client/ClientNetwork.h"
#include "client/Player.h"

int main() {

    float tickTimeAccumulator = 0.0f;

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

    gf::Clock clock;

    while (window.isOpen()) {
        // Process events
        float dt = clock.restart().asSeconds();

        // Envoyer packet ClientMove tout les 30tps (1 / 30)
        tickTimeAccumulator += dt;

        gf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case gf::EventType::Closed:
                    window.close();
                    networking.stop();
                    break; // TODO: Séparé input & update
                case gf::EventType::KeyPressed:
                case gf::EventType::KeyRepeated:

                    if (event.key.keycode == gf::Keycode::Right) {
                        player.move(100.0f * dt, 0);
                    }
                    if (event.key.keycode == gf::Keycode::Left) {
                        player.move(-100.0f * dt, 0);
                    }
                    if (event.key.keycode == gf::Keycode::Up) {
                        player.move(0, -100.0f * dt);
                    }
                    if (event.key.keycode == gf::Keycode::Down) {
                        player.move(0, 100.0f * dt);
                    }
                    break;
                default:
                    break;
            }
        }

        if (tickTimeAccumulator >= (1.0f / 30.0f)) {
            networking.send(ClientMove{player.x, player.y, player.rot});
            tickTimeAccumulator = 0.0f;
        }

        // Draw the entities
        renderer.clear();
        sprite.setPosition({ player.x, player.y });
        renderer.draw(sprite);
        renderer.draw(text);
        renderer.display();
    }
    return 0;
}
