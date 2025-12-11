#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <optional>
#include <sstream>
#include "Body.h"

class Renderer {
    private:
        sf::RenderWindow window;
        sf::Font robotoFont;
        bool fontAvailable = true;
        std::optional<sf::Text> fpsText;
        const unsigned int DISPLAY_COUNTER_MAX = 5;
        unsigned int fpsDisplayCounter = DISPLAY_COUNTER_MAX;
    public:
        Renderer();

        void drawBodies(std::vector<Body>& bodies);
        void processEvents();
        void drawFps(const float& deltaTime);
        void render(std::vector<Body>& bodies, const float& deltaTime);
        bool isWindowOpen();
};


#endif