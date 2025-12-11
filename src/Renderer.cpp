#include "../include/Renderer.h"

Renderer::Renderer() {
    // Window
    window = sf::RenderWindow(sf::VideoMode({800, 600}), "2D Gravity simulator");
    window.setFramerateLimit(60);
    // Font and text
    if (robotoFont.openFromFile("../assets/Roboto-Regular.ttf")) {
        fontAvailable = true;
        fpsText.emplace(robotoFont, "Fps display", 12);
        std::cout << "emplace" << '\n';
        fpsText->setFillColor(sf::Color::White);
    }
    else {
        std::cerr << "Warning: could not load font. Text will be disabled. \n";
    };

}

void Renderer::drawBodies(std::vector<Body>& bodies) {
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

void Renderer::drawFps(const float& deltaTime) {
    if (!fontAvailable || !fpsText.has_value()) {
        return;
    }

    fpsDisplayCounter --;
    if (fpsDisplayCounter == 0) {
        fpsDisplayCounter = DISPLAY_COUNTER_MAX;
        std::ostringstream ss;
        ss << std::fixed << std::setprecision(2) << 1/deltaTime << " fps";
        fpsText->setString(ss.str());
    }
    window.draw(*fpsText);
}

void Renderer::render(std::vector<Body>& bodies, const float& deltaTime) {
    window.clear();
    drawFps(deltaTime);
    drawBodies(bodies);
    window.display();
}

bool Renderer::isWindowOpen() {
    return window.isOpen();
}

