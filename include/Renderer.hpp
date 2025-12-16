#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include <sstream>

#include "Body.hpp"
#include "VecMath.hpp"
#include "BodyManager.hpp"

class Renderer {
    private:
        sf::RenderWindow window;
        const int N_VEL_PREVIEW_POINTS = 10;
        const int TRAJECTORY_POINT_RADIUS = 1;
        sf::Font robotoFont;
        bool fontAvailable = true;
        std::optional<sf::Text> fpsText;
        const int DISPLAY_COUNTER_MAX = 15;
        int fpsDisplayCounter = DISPLAY_COUNTER_MAX;
    public:
        Renderer();
        void drawTrajectory(const Body& body);
        void drawBody(const Body& body);
        void drawPreviewVel(const Body& body);
        void drawBodies(BodyManager& bodyManager);
        void drawFps(const float& deltaTime);
        void render(BodyManager& bodyManager, const float& deltaTime, const std::optional<Body>& previewBody);
        std::optional<sf::Event> pollEvent();
        void closeWindow();
        bool isWindowOpen();
        sf::Vector2i getMousePos();
};


#endif