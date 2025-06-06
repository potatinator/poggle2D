#ifndef GAME_H
#define GAME_H

#include <glm/glm.hpp>
#include <vector>
#include "gameobject.h"
#include "ui.h"
#include "gun.h"
#include "peg.h"
#include "save.h"
#include "ball.h"

class Game2D{
    public:
        bool keys[1024];
        bool oldKeys[1024];
        bool leftMouse;
        bool rightMouse;
        glm::vec2 mousePos;
        bool rightLast;
        bool leftLast;
        SaveMgr save;
        Gun* gun;
        Ball* ball;
        bool lastpressed;
        unsigned int width, height;
        bool wireframe;
        bool debug;
        std::vector<GameObject*> objects;
        std::vector<Peg*> pegs;        
        Game2D(unsigned int width, unsigned int height);
        ~Game2D();
        void update(float dt);
        void render();
        void processInputs();
        void init();
};

#endif