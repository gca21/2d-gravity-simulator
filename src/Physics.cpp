#include "Physics.hpp"

Physics::Physics(float gravitationalConstant) {
    G = gravitationalConstant;
}

float Physics::calculateGravityForce(Body& body1, Body& body2) const {
    float sqrDistance = (body1.getPos() - body2.getPos()).lengthSquared();
    if (sqrDistance == 0) {
        sqrDistance = 0.01;
    }
    return (G*body1.getMass()*body2.getMass()) / sqrDistance;
}

void Physics::simulateGravity(BodyManager& bodyManager) const {
    bodyManager.forEachBodyPairMutable([this](Body& body1, Body& body2) {
        if (body1.getId() == body2.getId()) {
            return;
        }
        float force = calculateGravityForce(body1, body2);
        sf::Vector2f forceVec = VecMath::calculateUnitVector(body1.getPos(), body2.getPos()) * force;
        body2.accelerate(forceVec / body2.getMass());
    });
}

void Physics::resetAcc(BodyManager& bodyManager) const {
    bodyManager.forEachBodyMutable([](Body& body) {
        body.setAcc({0, 0});
    });
}

void Physics::updateVel(BodyManager& bodyManager, float deltaTime) const {
    bodyManager.forEachBodyMutable([deltaTime](Body& body) {
        body.update(deltaTime);
    });
}

void Physics::simulation(BodyManager& bodyManager, float deltaTime) const {
    resetAcc(bodyManager);
    simulateGravity(bodyManager);
    updateVel(bodyManager, deltaTime);
}

void Physics::setG(float g) {
    G = g;
}

float Physics::getG() const {
    return G;
}