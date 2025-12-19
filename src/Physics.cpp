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

bool Physics::isColliding(Body& body1, Body& body2) const {
    if (body1.getId() == body2.getId()) {
        return false;
    }
    float distance = VecMath::calculateDistance(body1.getPos(), body2.getPos());
    return distance <= body1.getRadius() + body2.getRadius();
}

sf::Vector2f Physics::coalesceVelocity(const Body& body1, const Body& body2) const {
    float mass1 = body1.getMass();
    float mass2 = body2.getMass();
    sf::Vector2f vel1 = body1.getVel();
    sf::Vector2f vel2 = body2.getVel();
    return (mass1*vel1 + mass2*vel2) / (mass1 + mass2);
}

sf::Vector2f Physics::centerOfMass(const Body& body1, const Body& body2) const {
    sf::Vector2f pos1 = body1.getPos();
    sf::Vector2f pos2 = body2.getPos();
    float mass1 = body1.getMass();
    float mass2 = body2.getMass();
    return (pos1*mass1 + pos2*mass2) / (mass1 + mass2);
}

Body Physics::mergeBodies(const Body& body1, const Body& body2) const {
    // Calculate attributes
    sf::Vector2f pos = centerOfMass(body1, body2);
    sf::Vector2f vel = coalesceVelocity(body1, body2);
    float mass = body1.getMass() + body2.getMass();
    sf::Color color;
    if (body1.getMass() > body2.getMass()) {
        color = body1.getColor();
    }
    else {
        color = body2.getColor();
    }
    // Create and return the body
    return Body(
        pos,
        vel,
        {0, 0},
        mass,
        BodyManager::getRadiusFromMass(mass),
        color
    );
}

void Physics::mergeCollisions(BodyManager& bodyManager, std::vector<std::pair<int, int>>& collisions) const {
    std::unordered_set<int> merged; // Ids of bodies merged
    for (const auto& [id1, id2] : collisions) {
        // Skip merged bodies
        if (merged.count(id1) > 0 || merged.count(id2) > 0) {
            continue;
        }
        // Register as merged
        merged.insert(id1);
        merged.insert(id2);
        // Merge bodies
        Body& body1 = bodyManager.getBody(id1);
        Body& body2 = bodyManager.getBody(id2);
        Body merged = mergeBodies(body1, body2);
        // Update 
        bodyManager.addBody(merged);
        bodyManager.deleteBody(id1);
        bodyManager.deleteBody(id2);
    }
}

void Physics::findCollisions(BodyManager& bodyManager, std::vector<std::pair<int, int>>& collisions) const {
    bodyManager.forEachBodyPairMutable([this, &collisions, &bodyManager](Body& body1, Body& body2) {
        if (isColliding(body1, body2)) {
            std::pair<int, int> collision = std::make_pair(body1.getId(), body2.getId());
            collisions.push_back(collision);
        }
    });
}

void Physics::collisions(BodyManager& bodyManager) const {
    // Store collisions by bodies id
    std::vector<std::pair<int, int>> collisions;
    findCollisions(bodyManager, collisions);
    mergeCollisions(bodyManager, collisions);
}

void Physics::simulation(BodyManager& bodyManager, float deltaTime) const {
    resetAcc(bodyManager);
    simulateGravity(bodyManager);
    updateVel(bodyManager, deltaTime);
    collisions(bodyManager);
}

void Physics::setG(float g) {
    G = g;
}

float Physics::getG() const {
    return G;
}