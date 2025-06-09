#ifndef PEG_H
#define PEG_H

#include "gameobject.h"
class Peg : public TexturedGameObject{
    public:
        bool hit = false;
        Peg(glm::vec2 pos);
        void draw();
};

#endif