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

int main() {
    std::cout << "Hello, World Client!" << std::endl;

    ClientNetwork networking;
    networking.start();

    gf::Window window("Example", { 640, 480 });
    gf::RenderWindow renderer(window);
    renderer.clear(gf::Color::White);

    gf::Font font("DroidSans.ttf");

    gf::Text text("Hello gf!", font, 50);
    text.setColor(gf::Color4f(0.0f,0.0f,0.0f,1.0f));
    text.setPosition({ 100, 100 });

    while (window.isOpen()) {
        // Process events
        gf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case gf::EventType::Closed:
                    window.close();
                    networking.stop();
                    break;
                default:
                    break;
            }
        }
        // Draw the entities
        renderer.clear();
        //renderer.draw(sprite);
        renderer.draw(text);
        renderer.display();
    }
    return 0;
}
