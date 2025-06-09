#include "gun.h"
#include <iostream>
#include <glm/glm.hpp>

Gun::Gun(glm::vec2 pos, Texture2D tex, Ball* ball, glm::vec2 scale, int layer, float angle) : ball(ball), TexturedGameObject(pos, tex, scale, layer, angle){}

void Gun::update(float dt){
    glm::vec2 diff = (position+scale*0.5f) - mousePos;
    angle = -glm::degrees(atan(diff.x/diff.y))+90;
    TexturedGameObject::update(dt);
}
void Gun::draw(){
    TexturedGameObject::draw();
}
void Gun::shoot(){
    if(!ball->active){
        ball->active = true;
        count++;
        ball->position = position + scale/glm::vec2(2.0);
        ball->velocity = glm::vec2(-500.0) * glm::normalize((position+scale*0.5f) - mousePos);
    }
}