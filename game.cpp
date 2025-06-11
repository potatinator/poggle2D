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
    
    this->ball = new Ball(
        glm::vec2(400.0f, 300.0f),
        glm::vec2(10.0f, 0.0f),
        &pegs
    );
    this->gun = new Gun(
        glm::vec2(400.0f, -50.0f), // position
        Texture2D("./resources/gun.png", true),
        ball,
        glm::vec2(100.0f, 100.0f), // scale
        0
    );
    // this->path = new Path(
    //     glm::vec2(0.0f, 0.0f), // position
    //     glm::vec3(1.0),//col
    //     glm::vec2(width, height), // scale
    //     7
    // );

    objects.push_back(
        new TexturedGameObject(
            glm::vec2(0.0f, 0.0f), // position
            Texture2D("./resources/background.jpg", false),
            glm::vec2(width, height), // scale
            8
    ));
    objects.push_back(gun);
    objects.push_back(ball);
    // objects.push_back(path);
    
    pegs = save.load("save0.sav", pegs);
}
void Game2D::update(float dt){
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::ortho(0.0f, (float)width, (float)height, 0.0f, 0.0f, 10.0f);

    for(GameObject* object : objects){
        object->setDebug(debug);
        object->setView(view);
        object->update(dt);
    }

    for(Peg* object : pegs){
        if(object != nullptr){
            object->setDebug(debug);
            object->setView(view);
            object->update(dt);
        }
    }
    ball->collide();
    bool win = true;
    for(Peg* p : pegs){
        if(p != nullptr){
            win = false;
            break;
        }
    }
    if(win){
        std::cout << "win" << std::endl;
        lvl++;
        pegs = save.load("save" + std::to_string(lvl) +".sav", pegs);

        
    }
    win = true;
    for(Peg* p : pegs){
        if(p != nullptr){
            win = false;
            break;
        }
    }
    if(win){
        std::cout << "kill" << std::endl;
        return;
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

    for(Peg* object : pegs){
        if(object != nullptr){
            object->draw();
        }
    }
}

void Game2D::processInputs(){
    debug = keys[GLFW_KEY_S];
    wireframe = keys[GLFW_KEY_W] || this->debug;
    gun->mousePos = mousePos;

    if(leftMouse && ! leftLast){
        gun->shoot();
    }

    if(keys[GLFW_KEY_E] && !oldKeys[GLFW_KEY_E]){
        string s;
        cout << "enter save file to load: " << endl;
        cin >> s;
        pegs = save.load(s, pegs);
    }

    rightLast = rightMouse;
    leftLast = leftMouse;
    for(int i=0; i<sizeof(keys)/sizeof(bool); i++){
        oldKeys[i] = keys[i];
    }
}