#include "Universe.hpp"


Universe::Universe() {
    window = sf::RenderWindow(sf::VideoMode({800, 600}), "2D Gravity simulator");
    window.setFramerateLimit(60);
}

void Universe::processEvents() {
    leftMouseClickThisFrame = false;
    bool mouseMoved = false;
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mousePressed->button == sf::Mouse::Button::Left) {
                leftMouseClickThisFrame = true;
            }
        }
        else if (const auto* e = event->getIf<sf::Event::MouseMoved>()) {
            mouseMoved = true;
        }
    }

    if (leftMouseClickThisFrame && !leftMouseClickLastFrame) {
        sf::Vector2f mousePos(sf::Mouse::getPosition(window));
        bodyManager.addBody(bodies, previewBody, mousePos);
    }
    leftMouseClickLastFrame = leftMouseClickThisFrame;

    if (mouseMoved) {
        bodyManager.updatePreviewVel(previewBody, sf::Vector2f(sf::Mouse::getPosition(window)));
    }
}

void Universe::run() {
    sf::Clock clock;
    float accumulator = 0.0f;

    Body body1({300, 300}, {0, 0}, {0, 0}, 40000000, 20, sf::Color(255, 150, 100));
    bodies.push_back(body1);

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
        renderer.render(window, bodies, deltaTime, previewBody);
    }
}