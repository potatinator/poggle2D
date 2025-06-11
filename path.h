

#ifndef PATH_H
#define PATH_H

#include "texture.h"
#include "shader.h"
#include "gameobject.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

class Path : public GameObject {
    public:
        glm::vec3 color;
        glm::vec2 vel;
        glm::vec2 pos;

        // float vertices[12*7] = { // vertex attributes for a unit quad that fills the entire screen in Normalized Device Coordinates.
        //     // positions   // texCoords
        //     0.0f, 0.0f, 0.0f, 1.0f,
        //     0.1f, 0.0f, 1.0f, 0.0f,
        //     0.2f, 0.0f, 0.0f, 0.0f,

        //     0.2f, 0.0f, 0.0f, 1.0f,
        //     0.3f, 0.0f, 1.0f, 1.0f,
        //     0.35f, 0.0f, 1.0f, 0.0f,

        //     0.35f, 0.0f, 0.0f, 1.0f,
        //     0.4f, 0.0f, 1.0f, 1.0f,
        //     0.45f, 0.0f, 1.0f, 0.0f,
            
        //     0.45f, 0.0f, 1.0f, 0.0f,
        //     0.5f, 0.0f, 1.0f, 0.0f,
        //     0.55f, 0.0f, 1.0f, 0.0f,
            
        //     0.55f, 0.0f, 1.0f, 0.0f,
        //     0.6f, 0.0f, 1.0f, 0.0f,
        //     0.65f, 0.0f, 1.0f, 0.0f,
            
        //     0.65f, 0.0f, 0.0f, 1.0f,
        //     0.7f, 0.0f, 1.0f, 1.0f,
        //     0.8f, 0.0f, 1.0f, 0.0f,

        //     0.8f, 0.0f, 0.0f, 1.0f,
        //     0.9f, 0.0f, 1.0f, 1.0f,
        //     1.0f, 0.0f, 1.0f, 0.0f
        // };

        Path(glm::vec2 pos, glm::vec2 scale=glm::vec2(1.0f, 1.0f), int layer=0);
        void update(float dt);
        void draw();
        void setView(glm::mat4 view);
};
#endif


