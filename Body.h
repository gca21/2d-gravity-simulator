#ifndef BODY_H
#define BODY_H

#include <SFML/Graphics.hpp>

class Body {
    private:
        sf::Vector2f pos;
        sf::Vector2f vel;
        sf::Vector2f acc;
        float mass;
        int radius;
        sf::Color color;
    
    public:
        Body(sf::Vector2f p, sf::Vector2f v, sf::Vector2f a, float m, int r, sf::Color c);
        
        void draw(sf::RenderWindow& window);;
        void update(float deltaTime);
        void accelerate(sf::Vector2f acceleration);

        sf::Vector2f getPos();
        sf::Vector2f getVel();
        sf::Vector2f getAcc();
        float getMass();
        int getRadius();
        sf::Color getColor();

        void setPos(sf::Vector2f p);
        void setVel(sf::Vector2f v);
        void setAcc(sf::Vector2f a);
        void setMass(float m);
        void setRadius(int r);
        void setColor(sf::Color c);
};

#endif
