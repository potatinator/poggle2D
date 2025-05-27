

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "texture.h"
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GameObject{

    public:
        glm::vec2 position;
        float angle;
        glm::vec2 scale;
        glm::mat4 transform;
        Shader shader;
        unsigned int VAO;
        unsigned int VBO;
        float vertices[24] = { // vertex attributes for a unit quad that fills the entire screen in Normalized Device Coordinates.
            // positions   // texCoords
            0.0f,  0.0f, 0.0f, 1.0f,
            1.0f, -1.0f, 1.0f, 0.0f,
            0.0f, -1.0f, 0.0f, 0.0f, 

            0.0f,  0.0f, 0.0f, 1.0f,
            1.0f,  0.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f, 0.0f
        };
        int layer;

        GameObject(glm::vec2 pos, glm::vec2 scale, int layer, float angle, const Shader& shader);
        virtual void update(float dt);
        virtual void draw();
        virtual void setView(glm::mat4 view);
        virtual void setDebug(bool debug);
};
class TexturedGameObject : public GameObject {
    public:
        Texture2D texture;
        TexturedGameObject(glm::vec2 pos, Texture2D tex, glm::vec2 scale=glm::vec2(1.0f, 1.0f), int layer=0, float angle=0.0f);
        void update(float dt);
        void draw();
        void setView(glm::mat4 view);
};
class ColoredGameObject : public GameObject {
    public:
        glm::vec3 color;

        ColoredGameObject(glm::vec2 pos, glm::vec3 col, glm::vec2 scale=glm::vec2(1.0f, 1.0f), int layer=0, float angle=0.0f);
        void update(float dt);
        void draw();
        void setView(glm::mat4 view);
};
#endif

