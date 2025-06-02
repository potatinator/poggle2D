#include <iostream>
#include "ui.h"

Button::Button(glm::vec2 pos, glm::vec2 scale, int layer, float angle, std::shared_ptr<Shader> shader)
: GameObject(pos, scale, layer, angle, shader), hover(false), pressed(false), mousePos(0.0, 0.0) {}
Button::Button() {}
void Button::update(float dt){
    
    if(mousePos.x > position.x && mousePos.x < position.x + scale.x &&
       mousePos.y > position.y && mousePos.y < position.y + scale.y){
        hover = true;
        pressed = mousePressed;
    } else {
        hover = false;
        pressed = false;
    }
    
    GameObject::update(dt);
}
void Button::draw(){
    GameObject::draw();
}
// TexturedButton::TexturedButton(glm::vec2 pos, Texture2D tex, glm::vec2 scale, int layer, float angle)
//     : Button(pos, scale, layer, angle, Shader("./shaders/main.vert", "./shader/texture.frag")), idleTex(tex), hoverTex(tex), pressTex(tex){}
// TexturedButton::TexturedButton(glm::vec2 pos, Texture2D idleTex, Texture2D pressTex, glm::vec2 scale, int layer, float angle)
//     : Button(pos, scale, layer, angle, Shader("./shaders/main.vert", "./shader/texture.frag")), idleTex(idleTex), hoverTex(idleTex), pressTex(pressTex){}
// TexturedButton::TexturedButton(glm::vec2 pos, Texture2D idleTex, Texture2D hoverTex, Texture2D pressTex, glm::vec2 scale, int layer, float angle)
//     : Button(pos, scale, layer, angle, Shader("./shaders/main.vert", "./shader/texture.frag")), idleTex(idleTex), hoverTex(hoverTex), pressTex(pressTex){}

ColoredButton::ColoredButton(glm::vec2 pos, glm::vec3 col, glm::vec2 scale, int layer, float angle)
    : Button(pos, scale, layer, angle, std::make_shared<Shader>("./shaders/main.vert", "./shaders/color.frag")), idleCol(col), hoverCol(col), pressCol(col){}
ColoredButton::ColoredButton(glm::vec2 pos, glm::vec3 idleCol, glm::vec3 pressCol, glm::vec2 scale, int layer, float angle)
    : Button(pos, scale, layer, angle, std::make_shared<Shader>("./shaders/main.vert", "./shaders/color.frag")), idleCol(idleCol), hoverCol(idleCol), pressCol(pressCol){}
ColoredButton::ColoredButton(glm::vec2 pos, glm::vec3 idleCol, glm::vec3 hoverCol, glm::vec3 pressCol, glm::vec2 scale, int layer, float angle)
    : Button(pos, scale, layer, angle, std::make_shared<Shader>("./shaders/main.vert", "./shaders/color.frag")), idleCol(idleCol), hoverCol(hoverCol), pressCol(pressCol){}
void ColoredButton::update(float dt){
    Button::update(dt);
}
void ColoredButton::draw(){
    glm::vec3 color = idleCol;
    if(hover){
        color = hoverCol;
    }
    if(pressed){
        color = pressCol;
    }
    shader->use();
    shader->setVec3("color", color);
    GameObject::draw();
}