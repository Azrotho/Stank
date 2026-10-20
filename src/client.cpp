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

#include "common/Constants.h"

#include "client/ClientNetwork.h"
#include "client/Player.h"

int main() {
    std::cout << "Hello, World Client!" << std::endl;

    ClientNetwork networking;
    networking.start();

    gf::Texture texture("sprite/PNG/default/barrelRed_side.png");
    gf::Sprite sprite(texture);

    Player player;

    gf::Window window("Example", { 640, 480 });
    gf::RenderWindow renderer(window);
    renderer.clear(gf::Color::White);

    gf::Font font("DroidSans.ttf");

    gf::Text text("Hello gf!", font, 50);
    text.setColor(gf::Color4f(0.0f,0.0f,0.0f,1.0f));
    text.setPosition({ 100, 100 });

    gf::Clock clock;
    float dt = clock.restart().asSeconds();

    while (window.isOpen()) {
        // Process events
        gf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case gf::EventType::Closed:
                    window.close();
                    networking.stop();
                    break; // TODO: Séparé input & update
                case gf::EventType::KeyPressed:
                    if (event.key.keycode == gf::Keycode::Right) {
                        player.move(10 * dt, 0);
                    }
                    if (event.key.keycode == gf::Keycode::Left) {
                        player.move(-10 * dt, 0);
                    }
                    if (event.key.keycode == gf::Keycode::Up) {
                        player.move(0, -10 * dt);
                    }
                    if (event.key.keycode == gf::Keycode::Down) {
                        player.move(0, 10 * dt);
                    }
                    break;
                default:
                    break;
            }
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
