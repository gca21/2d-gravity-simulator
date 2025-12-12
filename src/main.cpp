#include <SFML/Graphics.hpp>
#include <vector>
#include "../include/Body.h"
#include "../include/Physics.h"
#include "../include/Renderer.h"

const float GRAVITATIONAL_CONSTANT = 0.1;
const unsigned int SIMULATIONS_PER_SECOND = 60;
const float SIMULATION_DELTA_TIME = (float)1/SIMULATIONS_PER_SECOND;


void processEvents(sf::RenderWindow& window) {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
    }
}

int main() {
    // Window
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({800, 600}), "2D Gravity simulator");
    window.setFramerateLimit(60);
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

    while (window.isOpen()) {
        // Get time between full iterations
        float deltaTime = clock.getElapsedTime().asSeconds();
        clock.restart();

        processEvents(window);

        // Simulate at fixed timestep
        accumulator += deltaTime;
        while (accumulator >= SIMULATION_DELTA_TIME) {
            physics.simulation(bodies, SIMULATION_DELTA_TIME);
            accumulator -= SIMULATION_DELTA_TIME;
        }
        // Render
        renderer.render(window, bodies, deltaTime);
    }
    return 0;
}