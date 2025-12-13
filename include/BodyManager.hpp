#ifndef BODYMANAGER_HPP
#define BODYMANAGER_HPP

#include <vector>

#include "Body.hpp"

class BodyManager {
    private:
        

    public:
        BodyManager();
        void addBody(std::vector<Body>& bodies, std::optional<Body>& previewBody, sf::Vector2f mousePos);

};


#endif