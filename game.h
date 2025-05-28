#ifndef GAME_H
#define GAME_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <vector>
#include <GLFW/glfw3.h>
#include "gameobject.h"


class Game2D{
    public:
        bool keys[1024];
        glm::vec2 mousePos;
        unsigned int width, height;
        bool wireframe;
        bool debug;
        std::vector<GameObject*> objects;        
        Game2D(unsigned int width, unsigned int height);
        ~Game2D();
        void update(float dt);
        void render();
        void processInputs();
        void init();
};

#endif