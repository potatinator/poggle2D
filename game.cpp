#include <glad/glad.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GLFW/glfw3.h>
#include "game.h"
#include "ui.h"

Game2D::Game2D(unsigned int width, unsigned int height) : width(width), height(height), keys(), mousePos(0.0, 0.0), wireframe(false), debug(false){}

Game2D::~Game2D(){
    //cleanup
}

void Game2D::init(){
    //load

    //NOTE: the new keyword generates a pointer, if the var is not a pointer(it has a *), dont use new
    this->button = new ColoredButton(
        glm::vec2(200.0f, 200.0f), // position
        glm::vec3(1.0f, 0.0f, 0.0f), // color
        glm::vec3(0.0f, 1.0f, 0.0f), // color
        glm::vec3(0.0f, 0.0f, 1.0f), // color
        glm::vec2(100.0f, 100.0f), // scale
        0
    );
    this->gun = new Gun(
        glm::vec2(400.0f, -50.0f), // position
        Texture2D("./resources/gun.png", true),
        glm::vec2(100.0f, 100.0f), // scale
        0
    );
    pegs.push_back(new Peg(
        glm::vec2(530.0f, 200.0f)
    ));
    pegs.push_back(new Peg(
        glm::vec2(560.0f, 200.0f)
    ));
    pegs.push_back(new Peg(
        glm::vec2(590.0f, 200.0f)
    ));
    pegs.push_back(new Peg(
        glm::vec2(610.0f, 200.0f)
    ));
    pegs.push_back(new Peg(
        glm::vec2(640.0f, 200.0f)
    ));

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
            8
    ));
    objects.push_back(
        new ColoredGameObject(
            glm::vec2(500.0f, 500.0f), // position
            glm::vec3(1.0, 0.0, 0.0),
            glm::vec2(80.0f, 60.0f), // scale
            0
    ));
    objects.push_back(button);
    objects.push_back(gun);
    for(Peg* peg : pegs ){
        objects.push_back(peg);
    }
    
    
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
    button->mousePos = mousePos;
    button->mousePressed = leftMouse;
    gun->mousePos = mousePos;
}