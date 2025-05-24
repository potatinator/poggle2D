

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject{
    glm::vec2 position;
    float angle;
    glm::vec2 scale;
    glm::mat4 transform;

    GameObject(glm::vec2 pos, float angle=0.0f, glm::vec2 scale=glm::vec2(1.0f, 1.0f));
    ~GameObject();
    void update(float dt);
};

#endif

