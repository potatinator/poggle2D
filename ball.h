#ifndef BALL_H
#define BALL_H

#include "gameobject.h"

class Ball : public TexturedGameObject{
    public:
        glm::vec2 velocity;
        Ball(glm::vec2 pos, glm::vec2 vel);
};

#endif