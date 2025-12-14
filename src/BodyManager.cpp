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
            DEFAULT_BODY_RADIUS*DEFAULT_BODY_RADIUS*MASS_GROWTH_FACTOR, 
            DEFAULT_BODY_RADIUS, 
            colors.at(0)
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
    previewBody->setMass(previewBody->getRadius()*previewBody->getRadius()*MASS_GROWTH_FACTOR);
}

void BodyManager::updatePreviewColor(std::optional<Body>& previewBody) {
    if (!previewBody) {
        return;
    }
    // Find the current color and change it to the next one
    for (size_t i = 0; i < colors.size(); i++) {
        if (colors.at(i) != previewBody->getColor()) {
            continue;
        }
        if (i == colors.size()-1) {
            previewBody->setColor(colors.at(0));
            return;
        }
        previewBody->setColor(colors.at(i+1));
        return;
    }
}
