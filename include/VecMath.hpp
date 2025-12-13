#ifndef VECMATH_HPP
#define VECMATH_HPP

#include <SFML/Graphics.hpp>

namespace VecMath {
    const float MINIMUM_DISTANCE = 0.01;

    // Calculates the unit vector from position2 to position1
    sf::Vector2f calculateUnitVector(const sf::Vector2f& pos1, const sf::Vector2f& pos2);
    float calculateDistance(const sf::Vector2f& pos1, const sf::Vector2f& pos2);

}

#endif