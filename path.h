

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

        Path(glm::vec2 pos, glm::vec3 col, glm::vec2 scale=glm::vec2(1.0f, 1.0f), int layer=0, float angle=0.0f);
        void update(float dt);
        void draw();
        void setView(glm::mat4 view);
};
#endif


