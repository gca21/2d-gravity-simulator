#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <optional>
#include <sstream>

#include "Body.hpp"

class Renderer {
    private:
        const int TRAJECTORY_POINT_RADIUS = 1;
        sf::Font robotoFont;
        bool fontAvailable = true;
        std::optional<sf::Text> fpsText;
        const unsigned int DISPLAY_COUNTER_MAX = 15;
        unsigned int fpsDisplayCounter = DISPLAY_COUNTER_MAX;
    public:
        Renderer();
        void drawTrajectory(sf::RenderWindow& window, const Body& body);
        void drawBody(sf::RenderWindow& window, const Body& body);
        void drawBodies(sf::RenderWindow& window, const std::vector<Body>& bodies);
        void drawFps(sf::RenderWindow& window, const float& deltaTime);
        void render(
            sf::RenderWindow& window, 
            const std::vector<Body>& bodies, 
            const float& deltaTime,
            const std::optional<Body>& previewBody
        );
};


#endif