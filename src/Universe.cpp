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
    bool cKeyPressed = false;
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
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::C) {
                cKeyPressed = true;
            }
        }
    }

    if (leftMouseClickThisFrame && !leftMouseClickLastFrame) {
        sf::Vector2f mousePos(sf::Mouse::getPosition(window));
        bodyManager.addBody(*this, mousePos);
    }
    leftMouseClickLastFrame = leftMouseClickThisFrame;

    if (mouseMoved) {
        bodyManager.updatePreviewVel(sf::Vector2f(sf::Mouse::getPosition(window)));
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

    while (window.isOpen()) {
        // Get time between full iterations
        float deltaTime = clock.getElapsedTime().asSeconds();
        clock.restart();

        processEvents();

        // Simulate at fixed timestep
        accumulator += deltaTime;
        while (accumulator >= SIMULATION_DELTA_TIME) {
            physics.simulation(*this, SIMULATION_DELTA_TIME);
            accumulator -= SIMULATION_DELTA_TIME;
        }
        // Render
        renderer.render(*this, deltaTime, bodyManager.getPreviewBody());
    }
}

void Universe::addBody(Body body) {
    bodies.insert({body.getId(), body});
}

Body Universe::getBody(int id) const {
    return bodies.at(id);
}

sf::RenderWindow& Universe::getWindow() {
    return window;
}

void Universe::forEachBody(std::function<void(const Body&)> func) const {
    for (const auto& [id, body] : bodies) {
        func(body);
    }
}

void Universe::forEachBodyMutable(std::function<void(Body&)> func) {
    for (auto& [id, body] : bodies) {
        func(body);
    }
}

void Universe::forEachBodyPairMutable(std::function<void(Body&, Body&)> func) {
    for (auto& [id1, body1] : bodies) {
        for (auto& [id2, body2] : bodies) {
            func(body1, body2);
        }
    }
}