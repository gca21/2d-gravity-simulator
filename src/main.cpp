#include <SFML/Graphics.hpp>
#include <vector>
#include "../include/Body.h"
#include "../include/Physics.h"
#include "../include/Renderer.h"

const float GRAVITATIONAL_CONSTANT = 0.1;
const unsigned int SIMULATIONS_PER_SECOND = 60;
const float SIMULATION_DELTA_TIME = (float)1/SIMULATIONS_PER_SECOND;

int main() {
    sf::Clock clock;
    float accumulator = 0.0f;

    std::vector<Body> bodies;
    Body body1({300, 300}, {0, 0}, {0, 0}, 40000000, 20, sf::Color(255, 150, 100));
    Body body2({500, 300}, {-60, -60}, {0, 0}, 15000, 5, sf::Color(255, 255, 255));
    Body body3({50, 300}, {60, 60}, {0, 0}, 15000, 5, sf::Color(255, 255, 255));
    bodies.push_back(body1);
    bodies.push_back(body2);
    bodies.push_back(body3);

    Physics physics(GRAVITATIONAL_CONSTANT);
    Renderer renderer;

    while (renderer.isWindowOpen()) {
        // Get time between full iterations
        float deltaTime = clock.getElapsedTime().asSeconds();
        clock.restart();

        renderer.processEvents();

        // Simulate at fixed timestep
        accumulator += deltaTime;
        while (accumulator >= SIMULATION_DELTA_TIME) {
            physics.simulation(bodies, SIMULATION_DELTA_TIME);
            accumulator -= SIMULATION_DELTA_TIME;
        }
        // Render
        renderer.render(bodies, deltaTime);
    }
    return 0;
}