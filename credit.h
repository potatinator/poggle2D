#ifndef CREDIT_H
#define CREDIT_H

#include <fstream>
#include <vector>
#include <glm/glm.hpp>
#include "text.h"

class Credit{
    public:
        std::ifstream file;
        int line;
        TextRenderer text;
        float speed = 25.0f;
        float pos = 0.0f;
        bool running = false;
        std::string out;
        Credit(std::string fileName);
        void init();
        void start();
        void stop();
        void update(float dt);
        void draw();
        void setView(glm::mat4 view);
};

#endif