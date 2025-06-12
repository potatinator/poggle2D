#ifndef PEG_H
#define PEG_H

#include "gameobject.h"
class Peg : public TexturedGameObject{
    public:
        bool hit = false;
        int hits = 0;
        Peg(glm::vec2 pos);
        Peg(glm::vec2 pos, bool orange);
        void draw();
        void setOrange(bool o);
        bool isOrange();
    private:
        bool orange = false;
    };
    
#endif