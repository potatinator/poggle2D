#include "peg.h"
#include "texture.h"
Peg::Peg(glm::vec2 pos) : TexturedGameObject(pos, Texture2D("./resources/ball2.png", true), glm::vec2(20.0f, 20.0f)) {};

void Peg::draw(){
    shader->use();
    exposure = hit ? 50 : 1;
    TexturedGameObject::draw();
}