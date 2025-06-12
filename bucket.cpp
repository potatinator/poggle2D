#include "ball.h"
#include "texture.h"
#include "bucket.h"
#include <iostream>

Bucket::Bucket() :  velocity(glm::vec2(50, 0)), TexturedGameObject(glm::vec2(0, 575), Texture2D("./resources/placeholder.png", true), glm::vec2(150, 50), 1) {};
void Bucket::update(float dt){
    position += velocity*dt;
    if(position.x < 0 || position.x+scale.x>800){
        velocity = -velocity;
    }
    TexturedGameObject::update(dt);

};
