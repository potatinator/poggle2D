#include "gun.h"
#include <iostream>

Gun::Gun(glm::vec2 pos, Texture2D tex, glm::vec2 scale, int layer, float angle) : TexturedGameObject(pos, tex, scale, layer, angle){}

void Gun::update(float dt){
    position = mousePos;
    TexturedGameObject::update(dt);
}
void Gun::draw(){
    TexturedGameObject::draw();
}