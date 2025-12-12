#include "../include/Universe.h"


Universe::Universe() {
    window = sf::RenderWindow(sf::VideoMode({800, 600}), "2D Gravity simulator");
    window.setFramerateLimit(60);
}

void Universe::processEvents() {
        while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            bodies.push_back(Body({500, 300}, {-60, -60}, {0, 0}, 15000, 5, sf::Color(255, 255, 255)));
        }
    }
}

void Universe::run() {
    sf::Clock clock;
    float accumulator = 0.0f;

    Body body1({300, 300}, {0, 0}, {0, 0}, 40000000, 20, sf::Color(255, 150, 100));
    Body body2({500, 300}, {-60, -60}, {0, 0}, 15000, 5, sf::Color(255, 255, 255));
    Body body3({50, 300}, {60, 60}, {0, 0}, 15000, 5, sf::Color(255, 255, 255));
    bodies.push_back(body1);
    bodies.push_back(body2);
    bodies.push_back(body3);

    while (window.isOpen()) {
        // Get time between full iterations
        float deltaTime = clock.getElapsedTime().asSeconds();
        clock.restart();

        processEvents();

        // Simulate at fixed timestep
        accumulator += deltaTime;
        while (accumulator >= SIMULATION_DELTA_TIME) {
            physics.simulation(bodies, SIMULATION_DELTA_TIME);
            accumulator -= SIMULATION_DELTA_TIME;
        }
        // Render
        renderer.render(window, bodies, deltaTime);
    }
}