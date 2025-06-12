#include "gun.h"
#include <iostream>
#include <glm/glm.hpp>

Gun::Gun(glm::vec2 pos, Texture2D tex, Ball* ball, glm::vec2 scale, int layer, float angle) : ball(ball), path(new Path(glm::vec2(0,0), glm::vec2(800,600), 7)), TexturedGameObject(pos, tex, scale, layer, 1.0, angle){}

void Gun::update(float dt){
    glm::vec2 diff = (position+scale*0.5f) - mousePos;
    angle = -glm::degrees(atan(diff.x/diff.y))+230;

    path->pos = position + scale/glm::vec2(2.0) - (ball->scale/glm::vec2(2.0) - 2.0f);
    path->vel = glm::vec2(-500.0) * glm::normalize((position+scale*0.5f) - mousePos);

    TexturedGameObject::update(dt);
    path->update(dt);
}
void Gun::draw(){
    TexturedGameObject::draw();
    path->draw();
}
void Gun::shoot(){
    if(!ball->active){
        ball->active = true;
        ball->position = position + scale/glm::vec2(2.0);
        ball->velocity = glm::vec2(-500.0) * glm::normalize((position+scale*0.5f) - mousePos);
        if(!ball->free){
            count--;
        }
        ball->free = false;
    }
}

void Gun::setView(glm::mat4 view){
    path->setView(view);
    TexturedGameObject::setView(view);
}