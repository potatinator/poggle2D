#include "gun.h"
#include <iostream>
#include <glm/glm.hpp>

Gun::Gun(glm::vec2 pos, Texture2D tex, glm::vec2 scale, int layer, float angle) : TexturedGameObject(pos, tex, scale, layer, angle){}

void Gun::update(float dt){
    glm::vec2 diff = (position+scale*0.5f) - mousePos;
    angle = -glm::degrees(atan(diff.x/diff.y))+90;
    TexturedGameObject::update(dt);
}
void Gun::draw(){
    TexturedGameObject::draw();
}