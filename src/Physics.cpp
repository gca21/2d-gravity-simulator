#include "Physics.hpp"
#include "Universe.hpp"

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

void Physics::simulateGravity(Universe& universe) const {
    universe.forEachBodyPairMutable([this](Body& body1, Body& body2) {
        if (body1.getId() == body2.getId()) {
            return;
        }
        float force = calculateGravityForce(body1, body2);
        sf::Vector2f forceVec = VecMath::calculateUnitVector(body1.getPos(), body2.getPos()) * force;
        body2.accelerate(forceVec / body2.getMass());
    });
}

void Physics::resetAcc(Universe& universe) const {
    universe.forEachBodyMutable([](Body& body) {
        body.setAcc({0, 0});
    });
}

void Physics::updateVel(Universe& universe, float deltaTime) const {
    universe.forEachBodyMutable([deltaTime](Body& body) {
        body.update(deltaTime);
    });
}

void Physics::simulation(Universe& universe, float deltaTime) const {
    resetAcc(universe);
    simulateGravity(universe);
    updateVel(universe, deltaTime);
}

void Physics::setG(float g) {
    G = g;
}

float Physics::getG() const {
    return G;
}