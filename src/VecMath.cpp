#include "../include/VecMath.hpp"

sf::Vector2f VecMath::calculateUnitVector(const sf::Vector2f& vec1, const sf::Vector2f& vec2) {
    sf::Vector2f difference =  vec1 - vec2;
    float distance = difference.length();
    if (distance == 0) {
        distance = MINIMUM_DISTANCE;
    }
    return difference / distance;
}

float VecMath::calculateDistance(const sf::Vector2f& pos1, const sf::Vector2f& pos2) {
    sf::Vector2f difference =  pos1 - pos2;
    return difference.length();
}

sf::Vector2f VecMath::calculateStep(const sf::Vector2f& pos1, const sf::Vector2f& pos2, int nSteps) {
    sf::Vector2f stepsVec = {(float)nSteps, (float)nSteps};
    sf::Vector2f step = (pos1 - pos2).componentWiseDiv(stepsVec);
    return step;
}