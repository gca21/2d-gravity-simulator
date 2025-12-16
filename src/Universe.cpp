#include "Universe.hpp"


Universe::Universe() {

}

void Universe::processEvents() {
    leftMouseClickThisFrame = false;
    bool mouseMoved = false;
    bool mouseScrolled = false;
    float mouseWheelDelta;
    bool cKeyPressed = false;
    while (const std::optional event = renderer.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            renderer.closeWindow();
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
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::C) {
                cKeyPressed = true;
            }
        }
    }

    if (leftMouseClickThisFrame && !leftMouseClickLastFrame) {
        bodyManager.addPreviewBody(sf::Vector2f(renderer.getMousePos()));
    }
    leftMouseClickLastFrame = leftMouseClickThisFrame;

    if (mouseMoved) {
        bodyManager.updatePreviewVel(sf::Vector2f(renderer.getMousePos()));
    }
    if (mouseScrolled) {
        bodyManager.updatePreviewSize(mouseWheelDelta);
    }
    if (cKeyPressed) {
        bodyManager.updatePreviewColor();
    }
}

void Universe::run() {
    sf::Clock clock;
    float accumulator = 0.0f;

    while (renderer.isWindowOpen()) {
        // Get time between full iterations
        float deltaTime = clock.getElapsedTime().asSeconds();
        clock.restart();

        processEvents();

        // Simulate at fixed timestep
        accumulator += deltaTime;
        while (accumulator >= SIMULATION_DELTA_TIME) {
            physics.simulation(bodyManager, SIMULATION_DELTA_TIME);
            accumulator -= SIMULATION_DELTA_TIME;
        }
        // Render
        renderer.render(bodyManager, deltaTime, bodyManager.getPreviewBody());
    }
}