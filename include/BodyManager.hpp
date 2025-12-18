#ifndef BODYMANAGER_HPP
#define BODYMANAGER_HPP

#include <unordered_map>
#include <array>

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
        void deleteBody(int bodyId);

        std::optional<Body> getPreviewBody() const;
        Body getBody(int id) const;

        template <typename Func>
        void forEachBody(Func func) const {
            for (const auto& [id, body] : bodies) {
                func(body);
            }
        }

        template <typename Func>
        void forEachBodyMutable(Func func) {
            for (auto& [id, body] : bodies) {
                func(body);
            }
        }

        template <typename Func>
        void forEachBodyPairMutable(Func func) {
            for (auto& [id1, body1] : bodies) {
                for (auto& [id2, body2] : bodies) {
                    func(body1, body2);
                }
            }
        }
};

#endif