#include <SFML/Graphics.hpp>
#include <vector>
#include "../include/Body.h"
#include "../include/Physics.h"
#include "../include/Renderer.h"

const float GRAVITATIONAL_CONSTANT = 0.1;

int main() {
    sf::Clock clock;

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
        // Get delta time
        float deltaTime = clock.getElapsedTime().asSeconds();
        clock.restart();

        renderer.processEvents();

        // Simulation
        physics.simulation(bodies, deltaTime);
        // Render
        renderer.render(bodies);
    }
    return 0;
}