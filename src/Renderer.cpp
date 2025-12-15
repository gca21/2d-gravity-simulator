#include "Renderer.hpp"

Renderer::Renderer() {
    // Window
    window = sf::RenderWindow(sf::VideoMode({1200, 900}), "2D Gravity simulator");
    window.setFramerateLimit(60);
    // Font and text
    if (robotoFont.openFromFile("../assets/Roboto-Regular.ttf")) {
        fontAvailable = true;
        fpsText.emplace(robotoFont, "", 12);
        fpsText->setFillColor(sf::Color::White);
    }
    else {
        std::cerr << "Warning: could not load font. Text will be disabled. \n";
    };

}

void Renderer::drawTrajectory(const Body& body) {
    for (const sf::Vector2f& oldPos : body.getTrajectory()) {
        sf::CircleShape circle;
        circle.setRadius(TRAJECTORY_POINT_RADIUS);
        circle.setFillColor(sf::Color(body.getColor().r, body.getColor().g, body.getColor().b, 100));
        circle.setPosition({oldPos.x - circle.getRadius(), oldPos.y - circle.getRadius()});
        window.draw(circle);
    }
}

void Renderer::drawBody(const Body& body) {
    drawTrajectory(body);
    // Draw circle
    sf::CircleShape circle;
    circle.setRadius(body.getRadius());
    circle.setFillColor(body.getColor());
    circle.setPosition({body.getPos().x - body.getRadius(), body.getPos().y - body.getRadius()});
    window.draw(circle);
}

void Renderer::drawPreviewVel(const Body& body) {
    sf::Vector2f lastPointPos = body.getPos() + body.getVel();
    sf::Vector2f step = VecMath::calculateStep(lastPointPos, body.getPos(), N_VEL_PREVIEW_POINTS);
    // Draw preview
    sf::CircleShape circle;
    circle.setRadius(TRAJECTORY_POINT_RADIUS);
    circle.setFillColor(sf::Color(body.getColor().r, body.getColor().g, body.getColor().b, 100));
    circle.setPosition({body.getPos().x - circle.getRadius(), body.getPos().y - circle.getRadius()});
    for (int i = 0; i < N_VEL_PREVIEW_POINTS; i++) {
        circle.setPosition(circle.getPosition() + step);
        window.draw(circle);
    }

}

void Renderer::drawBodies(BodyManager& bodyManager) {
    bodyManager.forEachBody([this](const Body& body) {
        drawBody(body);
    });
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

void Renderer::render(BodyManager& bodyManager, const float& deltaTime, const std::optional<Body>& previewBody) {
    window.clear();
    drawFps(deltaTime);
    drawBodies(bodyManager);
    if (previewBody) {
        drawBody(*previewBody);
        drawPreviewVel(*previewBody);
    }
    window.display();
}

std::optional<sf::Event> Renderer::pollEvent() {
    return window.pollEvent();
}

void Renderer::closeWindow() {
    window.close();
}

bool Renderer::isWindowOpen() {
    return window.isOpen();
}

sf::Vector2i Renderer::getMousePos() {
    return sf::Mouse::getPosition(window);
}
