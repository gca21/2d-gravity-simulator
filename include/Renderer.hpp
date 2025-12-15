#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <optional>
#include <sstream>

#include "Body.hpp"
#include "VecMath.hpp"

class Universe;

class Renderer {
    private:
        const int N_VEL_PREVIEW_POINTS = 10;
        const int TRAJECTORY_POINT_RADIUS = 1;
        sf::Font robotoFont;
        bool fontAvailable = true;
        std::optional<sf::Text> fpsText;
        const int DISPLAY_COUNTER_MAX = 15;
        int fpsDisplayCounter = DISPLAY_COUNTER_MAX;
    public:
        Renderer();
        void drawTrajectory(sf::RenderWindow& window, const Body& body);
        void drawBody(sf::RenderWindow& window, const Body& body);
        void drawPreviewVel(sf::RenderWindow& window, const Body& body);
        void drawBodies(Universe& universe);
        void drawFps(sf::RenderWindow& window, const float& deltaTime);
        void render(Universe& universe, const float& deltaTime, const std::optional<Body>& previewBody);
};


#endif