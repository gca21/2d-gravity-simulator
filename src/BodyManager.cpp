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
        previewBody.emplace(
            mousePos,
            vector0,
            vector0, 
            DEFAULT_BODY_MASS, 
            DEFAULT_BODY_RADIUS, 
            sf::Color(255, 255, 255)
        );
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

void BodyManager::updatePreviewSize(std::optional<Body>& previewBody, float mouseWheelDelta) {
    if (!previewBody) {
        return;
    }
    float currentMass = previewBody->getMass();
    // Avoid 0 values
    if (previewBody->getRadius() == DEFAULT_BODY_RADIUS && mouseWheelDelta == -1) {
        return;
    }
    // Update mass and radius
    previewBody->setRadius(previewBody->getRadius() + mouseWheelDelta*DEFAULT_BODY_RADIUS);
    if (mouseWheelDelta == 1) {
        previewBody->setMass(currentMass*3);
    }
    else {
        previewBody->setMass(currentMass/3);
    }
}
