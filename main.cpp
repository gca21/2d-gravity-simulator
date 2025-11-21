#include <SFML/Graphics.hpp>


struct object {
    sf::Vector2f pos;
    sf::Vector2f vel;
    sf::Vector2f acc;
    float mass;
    float radius;
};

int main() {

    sf::RenderWindow window(sf::VideoMode({800, 600}), "2D Gravity simulator");
    window.setFramerateLimit(60);

    sf::Clock clock;

    sf::Vector2f circlePos(300, 400);

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



        // Render
        window.clear();

        sf::CircleShape circle;
        circle.setRadius(50);
        circle.setOutlineColor(sf::Color::Red);
        circle.setOutlineThickness(5);
        circle.setPosition(circlePos);
        window.draw(circle);

        window.display();

        // Circle moves at 10 pixel per second
        circlePos.x = circlePos.x + 10*deltaTime;
    }
    return 0;
}