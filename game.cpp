#include "game.h"

Game2D::Game2D(unsigned int width, unsigned int height) : width(width), height(height), keys(), mousePos(0.0, 0.0), wireframe(false), debug(false){}

Game2D::~Game2D(){
    //cleanup
}

void Game2D::init(){
    //load

    objects.push_back(
        new TexturedGameObject(
            glm::vec2(0.0f, 0.0f), // position
            Texture2D("./resources/placeholder.png", true),
            glm::vec2(100.0f, 100.0f), // scale
            0
    ));
    objects.push_back(
        new TexturedGameObject(
            glm::vec2(0.0f, 0.0f), // position
            Texture2D("./resources/grid.png", true),
            glm::vec2(800.0f, 600.0f), // scale
            1
    ));
}
void Game2D::update(float dt){
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::ortho(0.0f, (float)width, (float)height, 0.0f, 0.0f, 10.0f);

    objects.at(0)->position = glm::vec2(width/2, height/2);
    objects.at(0)->angle += 50.0f * dt;
    
    objects.at(1)->position = glm::vec2(0.0f, 0.0f);

    for(GameObject* object : objects){
        object->setDebug(debug);
        object->setView(view);
        object->update(dt);
    }
}

void Game2D::render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    if(wireframe){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    for(GameObject* object : objects){
        object->draw();
    }
}

void Game2D::processInputs(){
    debug = keys[GLFW_KEY_S];
    wireframe = keys[GLFW_KEY_W] || this->debug;
}