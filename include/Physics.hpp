#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "Body.hpp"
#include "VecMath.hpp"

class Physics {
    private:
        float G;
    public:
        Physics(float gravitationalConstant);

        float calculateGravityForce(Body& body1, Body& body2) const;
        void simulateGravity(std::vector<Body>& bodies) const;
        void resetAcc(std::vector<Body>& bodies) const;
        void updateVel(std::vector<Body>& bodies, float deltaTime) const;
        void simulation(std::vector<Body>& bodies, float deltaTime) const;

        void setG(float g);
        float getG() const;
};


#endif