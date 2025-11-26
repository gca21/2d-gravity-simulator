#include "Body.h"

Body::Body(sf::Vector2f p, sf::Vector2f v, sf::Vector2f a, float m, int r, sf::Color c) {
    pos = p;
    vel = v;
    acc = a;
    mass = m;
    radius = r;
    color = c;
}

void Body::draw(sf::RenderWindow& window) {
    sf::CircleShape circle;
    circle.setRadius(radius);
    circle.setFillColor(color);
    circle.setPosition(pos);
    window.draw(circle);
}

void Body::update(float deltaTime) {
    vel += acc * deltaTime;
    pos += vel * deltaTime;
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
