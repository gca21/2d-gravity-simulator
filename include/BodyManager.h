#ifndef BODYMANAGER_H
#define BODYMANAGER_H

#include "../include/BodyManager.h"
#include "../include/Body.h"
#include <vector>

class BodyManager {
    private:
        

    public:
        BodyManager();
        void addBody(std::vector<Body>& bodies, std::optional<Body>& previewBody, sf::Vector2f mousePos);

};


#endif