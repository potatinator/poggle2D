#ifndef BUCKET_H
#define BUCKET_H

#include "gameobject.h"
#include <glm/glm.hpp>
#include <vector>

class Bucket : public TexturedGameObject{
    public:
        glm::vec2 velocity;

        Bucket();
        void update(float dt);
};

#endif