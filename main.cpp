#include <SFML/Graphics.hpp>
#include <vector>
#include "Body.h"

const float GRAVITATIONAL_CONSTANT = 0.1;

void renderBodies(sf::RenderWindow& window, std::vector<Body>& bodies) {
    for (Body& body : bodies) {
        body.draw(window);
    }
}

float calculateGravityForce(Body& body1, Body& body2) {
    float sqrDistance = (body1.getPos() - body2.getPos()).lengthSquared();
    return (GRAVITATIONAL_CONSTANT*body1.getMass()*body2.getMass()) / sqrDistance;
}

sf::Vector2f calculateUnitVector(Body& body1, Body& body2) {
    sf::Vector2f difference = body1.getPos() - body2.getPos();
    float distance = difference.length();
    return difference / distance;
}

void simulateGravity(std::vector<Body>& bodies) {
    for (unsigned int i = 0; i < bodies.size(); i++) {
        Body& body1 = bodies[i];
        for (unsigned int j = 0; j < bodies.size(); j++) {
            if (i == j) {
                continue;
            }
            Body& body2 = bodies[j];
            float force = calculateGravityForce(body1, body2);
            sf::Vector2f forceVec = calculateUnitVector(body1, body2) * force;
            body2.accelerate(forceVec / body2.getMass());
        }
    }
}

void resetAcc(std::vector<Body>& bodies) {
    for (Body& body : bodies) {
        body.setAcc({0, 0});
    }
}

void updateVel(std::vector<Body>& bodies, float deltaTime) {
    for (Body& body : bodies) {
        body.update(deltaTime);
    }
}

void simulation(std::vector<Body>& bodies, float deltaTime) {
    resetAcc(bodies);
    simulateGravity(bodies);
    updateVel(bodies, deltaTime);
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
        simulation(bodies, deltaTime);
        // Render
        window.clear();
        renderBodies(window, bodies);
        window.display();
    }
    return 0;
}