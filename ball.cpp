#include "ball.h"
#include "texture.h"
Ball::Ball(glm::vec2 pos) : velocity(vel), TexturedGameObject(pos, Texture2D("./resources/ball2.png", true), glm::vec2(20.0f, 20.0f)) {};