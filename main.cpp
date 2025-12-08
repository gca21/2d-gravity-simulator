#include <SFML/Graphics.hpp>
#include <vector>
#include "Body.h"
#include "Physics.h"

const float GRAVITATIONAL_CONSTANT = 0.1;

void renderBodies(sf::RenderWindow& window, std::vector<Body>& bodies) {
    for (Body& body : bodies) {
        body.draw(window);
    }
}

int main() {

    sf::RenderWindow window(sf::VideoMode({800, 600}), "2D Gravity simulator");
    window.setFramerateLimit(60);
    sf::Clock clock;

    std::vector<Body> bodies;
    Body body1({300, 300}, {0, 0}, {0, 0}, 40000000, 20, sf::Color(255, 150, 100));
    Body body2({500, 300}, {-60, -60}, {0, 0}, 15000, 5, sf::Color(255, 255, 255));
    Body body3({50, 300}, {60, 60}, {0, 0}, 15000, 5, sf::Color(255, 255, 255));
    bodies.push_back(body1);
    bodies.push_back(body2);
    bodies.push_back(body3);

    Physics physics(GRAVITATIONAL_CONSTANT);

    while (window.isOpen()) {
        // Get delta time
        float deltaTime = clock.getElapsedTime().asSeconds();
        clock.restart();

        // Process events
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // Simulation
        physics.simulation(bodies, deltaTime);
        // Render
        window.clear();
        renderBodies(window, bodies);
        window.display();
    }
    return 0;
}