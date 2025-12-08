#ifndef PHYSICS_H
#define PHYSICS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Body.h"

class Physics {
    private:
        float G;
    public:
        Physics(float gravitationalConstant);

        sf::Vector2f calculateUnitVector(Body& body1, Body& body2) const;
        float calculateGravityForce(Body& body1, Body& body2) const;
        void simulateGravity(std::vector<Body>& bodies) const;
        void resetAcc(std::vector<Body>& bodies) const;
        void updateVel(std::vector<Body>& bodies, float deltaTime) const;
        void simulation(std::vector<Body>& bodies, float deltaTime) const;

        void setG(float g);
        float getG() const;
};


#endif