#include "peg.h"
#include "texture.h"
Peg::Peg(glm::vec2 pos) : TexturedGameObject(pos, Texture2D("./resources/ball2.png", true), glm::vec2(20.0f, 20.0f)) {};
Peg::Peg(glm::vec2 pos, bool orange) : TexturedGameObject(pos, Texture2D("./resources/ball2.png", true), glm::vec2(20.0f, 20.0f)), orange(orange) {
    if(orange){
        texture = Texture2D("./resources/ball2orange.png", true);
    }
};

void Peg::draw(){
    shader->use();
    exposure = hit ? 50 : 1;
    TexturedGameObject::draw();
}

void Peg::setOrange(bool o){
    orange = o;
    if(orange){
        texture = Texture2D("./resources/ball2orange.png", true);
    } else {
        texture = Texture2D("./resources/ball2.png", true);
    }
}
bool Peg::isOrange(){
    return orange;
}