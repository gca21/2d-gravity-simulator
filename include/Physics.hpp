#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <SFML/Graphics.hpp>

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
        void simulation(BodyManager& bodyManager, float deltaTime) const;

        void setG(float g);
        float getG() const;
};


#endif