#include "Universe.hpp"


Universe::Universe() {
    window = sf::RenderWindow(sf::VideoMode({1200, 900}), "2D Gravity simulator");
    window.setFramerateLimit(60);
}

void Universe::processEvents() {
    leftMouseClickThisFrame = false;
    bool mouseMoved = false;
    bool mouseScrolled = false;
    float mouseWheelDelta;
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
        else if (const auto* e = event->getIf<sf::Event::MouseWheelScrolled>()) {
            mouseScrolled = true;
            mouseWheelDelta = e->delta;
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
    if (mouseScrolled) {
        bodyManager.updatePreviewSize(previewBody, mouseWheelDelta);
    }
}

void Universe::run() {
    sf::Clock clock;
    float accumulator = 0.0f;

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