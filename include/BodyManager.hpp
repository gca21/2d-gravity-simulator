#ifndef BODYMANAGER_HPP
#define BODYMANAGER_HPP

#include <vector>
#include <array>

#include "Body.hpp"
#include "VecMath.hpp"

class BodyManager {
    private:
        const int DEFAULT_BODY_RADIUS = 5;
        const int MASS_GROWTH_FACTOR = 1000;
        std::array <sf::Color, 7> colors{
            sf::Color::White, 
            sf::Color::Red,
            sf::Color::Green,
            sf::Color::Blue,
            sf::Color::Yellow,
            sf::Color::Magenta,
            sf::Color::Cyan
        };

    public:
        BodyManager();
        void addBody(std::vector<Body>& bodies, std::optional<Body>& previewBody, sf::Vector2f mousePos);
        void updatePreviewVel(std::optional<Body>& previewBody, sf::Vector2f mousePos);
        void updatePreviewSize(std::optional<Body>& previewBody, float mouseWheelDelta);
        void updatePreviewColor(std::optional<Body>& previewBody);

};


#endif