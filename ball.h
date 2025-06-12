#ifndef BALL_H
#define BALL_H

#include "gameobject.h"
#include "peg.h"
#include "freezone.h"
#include <glm/glm.hpp>
#include <vector>

class Ball : public TexturedGameObject{
    public:
        glm::vec2 velocity;
        bool active;
        bool free;
        Freezone* freeZone;
        std::vector<int> hits;
        std::vector<Peg*>* pegs;
        Ball(glm::vec2 pos, glm::vec2 vel, std::vector<Peg*>* pegs);
        void update(float dt);
        void collide();
};

#endif