#ifndef GAME_H
#define GAME_H

#include <glm/glm.hpp>
#include <vector>
#include "gameobject.h"
#include "ui.h"


class Game2D{
    public:
        bool keys[1024];
        bool leftMouse;
        bool rightMouse;
        glm::vec2 mousePos;
        ColoredButton* button;
        unsigned int width, height;
        bool wireframe;
        bool debug;
        std::vector<GameObject*> objects;        
        Game2D(unsigned int width, unsigned int height);
        ~Game2D();
        void update(float dt);
        void render();
        void processInputs();
        void init();
};

#endif