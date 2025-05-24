#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "gameobject.h"

GameObject::GameObject(glm::vec2 pos, float angle, glm::vec2 scale) : position(pos), scale(scale), angle(angle){
    this->update(0.0);
}
GameObject::~GameObject(){
    
}
void GameObject::update(float dt){
    transform = glm::mat4(1.0);
    transform = glm::translate(transform, glm::vec3(this->position, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    transform = glm::translate(transform, glm::vec3(0.5f * this->scale.x, 0.5f * this->scale.y, 0.0f)); // move origin of rotation to center of quad
    transform = glm::rotate(transform, glm::radians(this->angle), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    transform = glm::translate(transform, glm::vec3(-0.5f * this->scale.x, -0.5f * this->scale.y, 0.0f)); // move origin back

    transform = glm::scale(transform, glm::vec3(this->scale, 1.0f)); // last scale
}


