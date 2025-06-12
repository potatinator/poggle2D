#ifndef FREEZONE_H
#define FREEZONE_H

#include "gameobject.h"
#include <glm/glm.hpp>
#include <vector>

class Freezone : public TexturedGameObject{
    public:
        glm::vec2 velocity;

        Freezone();
        void update(float dt);
};

#endif