#ifndef GUN_H
#define GUN_H

#include "gameobject.h"
#include <glm/glm.hpp>

class Gun : public TexturedGameObject{
    public:
        glm::vec2 mousePos;
        Gun(glm::vec2 pos, Texture2D tex, glm::vec2 scale=glm::vec2(1.0f, 1.0f), int layer=0, float angle=0.0f);
        void update(float dt);
        void draw();

};

#endif
