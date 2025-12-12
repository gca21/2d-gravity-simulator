#include "../include/Physics.h"

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

void Physics::simulateGravity(std::vector<Body>& bodies) const {
    for (unsigned int i = 0; i < bodies.size(); i++) {
        Body& body1 = bodies[i];
        for (unsigned int j = 0; j < bodies.size(); j++) {
            if (i == j) {
                continue;
            }
            Body& body2 = bodies[j];
            float force = calculateGravityForce(body1, body2);
            sf::Vector2f forceVec = VecMath::calculateUnitVector(body1.getPos(), body2.getPos()) * force;
            body2.accelerate(forceVec / body2.getMass());
        }
    }
}

void Physics::resetAcc(std::vector<Body>& bodies) const {
    for (Body& body : bodies) {
        body.setAcc({0, 0});
    }
}

void Physics::updateVel(std::vector<Body>& bodies, float deltaTime) const {
    for (Body& body : bodies) {
        body.update(deltaTime);
    }
}

void Physics::simulation(std::vector<Body>& bodies, float deltaTime) const {
    resetAcc(bodies);
    simulateGravity(bodies);
    updateVel(bodies, deltaTime);
}

void Physics::setG(float g) {
    G = g;
}

float Physics::getG() const {
    return G;
}