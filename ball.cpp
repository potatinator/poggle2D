#include "ball.h"
#include "texture.h"
#include <iostream>

Ball::Ball(glm::vec2 pos, glm::vec2 vel, std::vector<Peg*>* pegs) : pegs(pegs), velocity(vel), active(false), TexturedGameObject(pos, Texture2D("./resources/ball1.png", true), glm::vec2(15.0f), 2) {};
void Ball::update(float dt){
    if(active){
        velocity += glm::vec2(0.0, 500.0)*dt;

        position += velocity*dt;
        if(position.y > 600){
            active = false;
            for(int h : hits){
                pegs->at(h) = nullptr;
            }
            hits.clear();
            if(position.x+scale.x > bucket->position.x && position.x < bucket->position.x+bucket->scale.x){
                free = true;
            }
        }
        TexturedGameObject::update(dt);
    }
};

void Ball::collide(){
    if(active){
        for (int i = 0; i < pegs->size(); i++){
            if(pegs->at(i) != nullptr){
                glm::vec2 diff = position - pegs->at(i)->position;
                if(glm::length(diff) <= scale.x/2.0+pegs->at(i)->scale.x/2.0){
                    position += glm::vec2((20.0-glm::length(diff))) * glm::normalize(diff); //position resolution
                    velocity = velocity - glm::vec2(1.75) * glm::dot(velocity, glm::normalize(diff)) * glm::normalize(diff);
                    hits.push_back(i);
                    pegs->at(i)->hit = true;
                }  
            } 
        }
        if(position.x < 0.0){
            position.x = 0.0;
            velocity.x = abs(velocity.x);
        }
        if(position.x > 800.0){
            position.x = 800.0;
            velocity.x = -abs(velocity.x);
        }
        if(position.y < 0){
            position.y = 0.0;
            velocity.y = abs(velocity.y);
        }
    }
}