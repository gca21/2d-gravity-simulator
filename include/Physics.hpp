#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_set>

#include "Body.hpp"
#include "VecMath.hpp"
#include "BodyManager.hpp"

class Physics {
    private:
        float G;
    public:
        Physics(float gravitationalConstant);

        float calculateGravityForce(Body& body1, Body& body2) const;
        void simulateGravity(BodyManager& bodyManager) const;
        void resetAcc(BodyManager& bodyManager) const;
        void updateVel(BodyManager& bodyManager, float deltaTime) const;
        bool isColliding(Body& body1, Body& body2) const;
        sf::Vector2f coalesceVelocity(const Body& body1, const Body& body2) const;
        sf::Vector2f centerOfMass(const Body& body1, const Body& body2) const;
        Body mergeBodies(const Body& body1, const Body& body2) const;
        void mergeCollisions(BodyManager& bodyManager, std::vector<std::pair<int, int>>& collisions) const;
        void findCollisions(BodyManager& bodyManager, std::vector<std::pair<int, int>>& collisions) const;
        void collisions(BodyManager& bodyManager) const;
        void simulation(BodyManager& bodyManager, float deltaTime) const;

        void setG(float g);
        float getG() const;
};


#endif