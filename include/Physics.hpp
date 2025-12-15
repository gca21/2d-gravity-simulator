#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "Body.hpp"
#include "VecMath.hpp"

class Universe;

class Physics {
    private:
        float G;
    public:
        Physics(float gravitationalConstant);

        float calculateGravityForce(Body& body1, Body& body2) const;
        void simulateGravity(Universe& universe) const;
        void resetAcc(Universe& universe) const;
        void updateVel(Universe& universe, float deltaTime) const;
        void simulation(Universe& universe, float deltaTime) const;

        void setG(float g);
        float getG() const;
};


#endif