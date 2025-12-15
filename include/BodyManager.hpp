#ifndef BODYMANAGER_HPP
#define BODYMANAGER_HPP

#include <unordered_map>
#include <array>
#include <functional>

#include "Body.hpp"
#include "VecMath.hpp"

class BodyManager {
    private:
        std::unordered_map<int,Body> bodies;
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
        void addPreviewBody(sf::Vector2f mousePos);
        void updatePreviewVel(sf::Vector2f mousePos);
        void updatePreviewSize(float mouseWheelDelta);
        void updatePreviewColor();
        void addBody(Body body);
        void forEachBody(std::function<void(const Body&)> func) const;
        void forEachBodyMutable(std::function<void(Body&)> func);
        void forEachBodyPairMutable(std::function<void(Body&, Body&)> func);

        std::optional<Body> getPreviewBody() const;
        Body getBody(int id) const;
};


#endif