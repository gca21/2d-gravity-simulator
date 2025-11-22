#include <SFML/Graphics.hpp>
#include <vector>

const float GRAVITATIONAL_CONSTANT = 0.1;

struct Body {
    sf::Vector2f pos;
    sf::Vector2f vel;
    sf::Vector2f acc;
    float mass;
    int radius;
    sf::Color color;

    Body(sf::Vector2f p, sf::Vector2f v, sf::Vector2f a, float m, int r, sf::Color c) {
        pos = p;
        vel = v;
        acc = a;
        mass = m;
        radius = r;
        color = c;
    }
};

void drawBody(sf::RenderWindow& window, Body& body) {
    sf::CircleShape circle;
    circle.setRadius(body.radius);
    circle.setFillColor(body.color);
    circle.setPosition(body.pos);
    window.draw(circle);

}

void renderBodies(sf::RenderWindow& window, std::vector<Body>& bodies) {
    for (Body& body : bodies) {
        drawBody(window, body);
    }
}

float calculateGravityForce(Body& body1, Body& body2) {
    float sqrDistance = (body1.pos - body2.pos).lengthSquared();
    return (GRAVITATIONAL_CONSTANT*body1.mass*body2.mass) / sqrDistance;
}

sf::Vector2f calculateUnitVector(Body& body1, Body& body2) {
    sf::Vector2f difference = body1.pos - body2.pos;
    float distance = difference.length();
    return difference / distance;
}

void simulateGravity(std::vector<Body>& bodies) {
    for (unsigned int i = 0; i < bodies.size(); i++) {
        Body body1 = bodies[i];
        for (unsigned int j = 0; j < bodies.size(); j++) {
            Body body2 = bodies[j];
            if (i != j) {
                float force = calculateGravityForce(body1, body2);
                sf::Vector2f forceVec = calculateUnitVector(body1, body2) * force;
                bodies[j].acc += forceVec / body2.mass;
            }
        }
    }
}

void resetAcc(std::vector<Body>& bodies) {
    for (Body& body : bodies) {
        body.acc = {0, 0};
    }
}

void updateVel(std::vector<Body>& bodies) {
    for (Body& body : bodies) {
        body.vel += body.acc;
        body.pos += body.vel;
    }
}

void simulation(std::vector<Body>& bodies) {
    resetAcc(bodies);
    simulateGravity(bodies);
    updateVel(bodies);
}

int main() {

    sf::RenderWindow window(sf::VideoMode({800, 600}), "2D Gravity simulator");
    window.setFramerateLimit(60);
    sf::Clock clock;

    std::vector<Body> bodies;
    Body body1({300, 300}, {0, 0}, {0, 0}, 10000, 20, sf::Color(250, 150, 100));
    Body body2({500, 300}, {-1, -1}, {0, 0}, 250, 5, sf::Color(250, 250, 250));
    bodies.push_back(body1);
    bodies.push_back(body2);

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
        simulation(bodies);
        // Render
        window.clear();
        renderBodies(window, bodies);
        window.display();
    }
    return 0;
}