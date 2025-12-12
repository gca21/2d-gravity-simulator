#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "../include/Body.h"
#include "../include/Physics.h"
#include "../include/Renderer.h"
#include "../include/BodyManager.h"
#include <vector>


class Universe {
    private:
        float GRAVITATIONAL_CONSTANT = 0.1;
        const unsigned int SIMULATIONS_PER_SECOND = 60;
        const float SIMULATION_DELTA_TIME = (float)1/SIMULATIONS_PER_SECOND;
        sf::RenderWindow window;
        std::vector<Body> bodies;
        Physics physics = Physics(GRAVITATIONAL_CONSTANT);
        Renderer renderer;
        BodyManager bodyManager;
        std::optional<Body> previewBody; // New body created by user
        // Anti-spam for creating bodies
        bool leftMouseClickThisFrame = false;
        bool leftMouseClickLastFrame = false;
    public:
        Universe();
        void processEvents();
        void run();

};


#endif