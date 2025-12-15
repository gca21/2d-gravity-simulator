#include "Renderer.hpp"
#include "Universe.hpp"

Renderer::Renderer() {
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

void Renderer::drawTrajectory(sf::RenderWindow& window, const Body& body) {
    for (const sf::Vector2f& oldPos : body.getTrajectory()) {
        sf::CircleShape circle;
        circle.setRadius(TRAJECTORY_POINT_RADIUS);
        circle.setFillColor(sf::Color(body.getColor().r, body.getColor().g, body.getColor().b, 100));
        circle.setPosition({oldPos.x - circle.getRadius(), oldPos.y - circle.getRadius()});
        window.draw(circle);
    }
}

void Renderer::drawBody(sf::RenderWindow& window, const Body& body) {
    drawTrajectory(window, body);
    // Draw circle
    sf::CircleShape circle;
    circle.setRadius(body.getRadius());
    circle.setFillColor(body.getColor());
    circle.setPosition({body.getPos().x - body.getRadius(), body.getPos().y - body.getRadius()});
    window.draw(circle);
}

void Renderer::drawPreviewVel(sf::RenderWindow& window, const Body& body) {
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

void Renderer::drawBodies(Universe& universe) {
    universe.forEachBody([this, &window=universe.getWindow()](const Body& body) {
        drawBody(window, body);
    });
}

void Renderer::drawFps(sf::RenderWindow& window, const float& deltaTime) {
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

void Renderer::render(Universe& universe, const float& deltaTime, const std::optional<Body>& previewBody) {
    sf::RenderWindow& window = universe.getWindow();
    window.clear();
    drawFps(window, deltaTime);
    drawBodies(universe);
    if (previewBody) {
        drawBody(window, *previewBody);
        drawPreviewVel(window, *previewBody);
    }
    window.display();
}

