#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <unordered_map>
#include <functional>

#include "Body.hpp"
#include "BodyManager.hpp"
#include "Physics.hpp"
#include "Renderer.hpp"

class Universe {
    private:
        float GRAVITATIONAL_CONSTANT = 0.1;
        const unsigned int SIMULATIONS_PER_SECOND = 60;
        const float SIMULATION_DELTA_TIME = (float)1/SIMULATIONS_PER_SECOND;
        sf::RenderWindow window;
        std::unordered_map<int,Body> bodies;
        Physics physics = Physics(GRAVITATIONAL_CONSTANT);
        Renderer renderer;
        BodyManager bodyManager;
        bool leftMouseClickThisFrame = false;
        bool leftMouseClickLastFrame = false;
    public:
        Universe();
        void processEvents();
        void run();
        void addBody(Body body);
        void forEachBody(std::function<void(const Body&)> func) const;
        void forEachBodyMutable(std::function<void(Body&)> func);
        void forEachBodyPairMutable(std::function<void(Body&, Body&)> func);

        Body getBody(int id) const;
        sf::RenderWindow& getWindow();

};


#endif