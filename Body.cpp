#include "Body.h"

Body::Body(sf::Vector2f p, sf::Vector2f v, sf::Vector2f a, float m, int r, sf::Color c) {
    pos = p;
    vel = v;
    acc = a;
    mass = m;
    radius = r;
    color = c;
}

void Body::drawTrajectory(sf::RenderWindow& window) {
    for (sf::Vector2f oldPos : trajectory) {
        sf::CircleShape circle;
        circle.setRadius(TRAJECTORY_POINT_RADIUS);
        circle.setFillColor(sf::Color(color.r, color.g, color.b, 100));
        circle.setPosition({oldPos.x + radius, oldPos.y + radius});
        window.draw(circle);
    }
}

void Body::draw(sf::RenderWindow& window) {
    drawTrajectory(window);
    sf::CircleShape circle;
    circle.setRadius(radius);
    circle.setFillColor(color);
    circle.setPosition(pos);
    window.draw(circle);
}

void Body::update(float deltaTime) {
    // Update velocity and position
    vel += acc * deltaTime;
    pos += vel * deltaTime;
    // Update trajectory
    if (trajectory.empty()) {
        trajectory.push_back(pos);
        return;
    }
    if ((trajectory.back() - pos).length() < MIN_TRAJECTORY_DISTANCE) {
        return;
    }
    if (trajectory.size() == MAX_TRAJECTORY_SIZE) {
        trajectory.pop_front();
    }
    trajectory.push_back(pos);

}

void Body::accelerate(sf::Vector2f acceleration) {
    acc += acceleration;
}

sf::Vector2f Body::getPos() {
    return pos;
}

sf::Vector2f Body::getVel() {
    return vel;
}

sf::Vector2f Body::getAcc() {
    return acc;
}

float Body::getMass() {
    return mass;
}

int Body::getRadius() {
    return radius;
}

sf::Color Body::getColor() {
    return color;
}

void Body::setPos(sf::Vector2f p) {
    pos = p;
}

void Body::setVel(sf::Vector2f v) {
    vel = v;
}

void Body::setAcc(sf::Vector2f a) {
    acc = a;
}

void Body::setMass(float m) {
    mass = m;
}

void Body::setRadius(int r) {
    radius = r;
}

void Body::setColor(sf::Color c) {
    color = c;
}
