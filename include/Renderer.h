#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Body.h"

class Renderer {
    private:
        sf::RenderWindow window;
    public:
        Renderer();

        void renderBodies(std::vector<Body>& bodies);
        void processEvents();
        void render(std::vector<Body>& bodies);
        bool isWindowOpen();
};


#endif