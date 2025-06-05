#ifndef BAL_H
#define BAL_H

#include "gameobject.h"
class Ball : public TexturedGameObject{
    public:
        glm::vec2 veocity;
        Ball(glm::vec2 pos, glm::vec2 vel);
};

#endif