#include "../include/Body.h"

Body::Body(sf::Vector2f p, sf::Vector2f v, sf::Vector2f a, float m, int r, sf::Color c) {
    pos = p;
    vel = v;
    acc = a;
    mass = m;
    radius = r;
    color = c;
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

sf::Vector2f Body::getPos() const {
    return pos;
}

sf::Vector2f Body::getVel() const {
    return vel;
}

sf::Vector2f Body::getAcc() const {
    return acc;
}

float Body::getMass() const {
    return mass;
}

int Body::getRadius() const {
    return radius;
}

sf::Color Body::getColor() const {
    return color;
}

const std::deque<sf::Vector2f>& Body::getTrajectory() const {
    return trajectory;
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
