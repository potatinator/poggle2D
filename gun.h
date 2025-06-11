#ifndef GUN_H
#define GUN_H

#include "gameobject.h"
#include "ball.h"
#include "path.h"
#include <glm/glm.hpp>

class Gun : public TexturedGameObject{
    public:
        glm::vec2 mousePos;
        Ball* ball;
        Path* path;
        int count = 0;
        Gun(glm::vec2 pos, Texture2D tex, Ball* ball, glm::vec2 scale=glm::vec2(1.0f, 1.0f), int layer=0, float angle=0.0f);
        void update(float dt);
        void draw();
        void shoot();
        void setView(glm::mat4 view);

};

#endif
