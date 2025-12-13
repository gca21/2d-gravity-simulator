#include "BodyManager.hpp"

BodyManager::BodyManager() {

}

void BodyManager::addBody(std::vector<Body>& bodies, std::optional<Body>& previewBody, sf::Vector2f mousePos) {
    if (previewBody) {
        bodies.push_back(*previewBody);
        previewBody.reset();
    }
    else {
        sf::Vector2f vector0 = {0, 0};
        previewBody.emplace(mousePos, vector0, vector0, 15000, 5, sf::Color(255, 255, 255));
    }
}

void BodyManager::updatePreviewVel(std::optional<Body>& previewBody, sf::Vector2f mousePos) {
    if (!previewBody) {
        return;
    }
    sf::Vector2f bodyPos = previewBody->getPos();
    sf::Vector2f unitVector = VecMath::calculateUnitVector(bodyPos, mousePos);
    float distance = VecMath::calculateDistance(mousePos, bodyPos);
    previewBody->setVel(unitVector*distance);
}