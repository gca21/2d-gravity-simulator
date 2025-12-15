#ifndef BODYMANAGER_HPP
#define BODYMANAGER_HPP

#include <vector>
#include <array>

#include "Body.hpp"
#include "VecMath.hpp"

class Universe;

class BodyManager {
    private:
        std::optional<Body> previewBody; // New body created by user
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
        void addBody(Universe& universe, sf::Vector2f mousePos);
        void updatePreviewVel(sf::Vector2f mousePos);
        void updatePreviewSize(float mouseWheelDelta);
        void updatePreviewColor();

        std::optional<Body> getPreviewBody() const;
};


#endif