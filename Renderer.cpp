#include "Renderer.h"

Renderer::Renderer() {
    window = sf::RenderWindow(sf::VideoMode({800, 600}), "2D Gravity simulator");
    window.setFramerateLimit(60);
}

void Renderer::renderBodies(std::vector<Body>& bodies) {
    for (Body& body : bodies) {
        body.draw(window);
    }
}

void Renderer::processEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
    }
}

void Renderer::render(std::vector<Body>& bodies) {
    window.clear();
    renderBodies(bodies);
    window.display();
}

bool Renderer::isWindowOpen() {
    return window.isOpen();
}

