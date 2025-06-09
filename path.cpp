#include "path.h"


Path::Path(glm::vec2 pos, glm::vec3 col, glm::vec2 scale, int layer, float angle)
    : GameObject(pos, scale, layer, angle, std::make_shared<Shader>("./shaders/main.vert", "./shaders/path.frag")), color(col) {
        
}
void Path::update(float dt){
    GameObject::update(dt);
}
void Path::draw(){
    shader->use();
    shader->setVec2("u_resolution", glm::vec2(800, 600));
    shader->setVec2("u_x0", glm::vec2(400, 0));
    shader->setVec2("u_v0", glm::vec2(5, 0));
    shader->setVec2("u_lambda", glm::vec2(0, 0.99));
    shader->setFloat("u_g", 5.0);
    shader->setFloat("u_maxTime", 1000);
    shader->setFloat("u_thickness", 10);
    shader->setMat3("u_worldToScreen", glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, 0.0f, 10.0f));
    GameObject::draw();
}
void Path::setView(glm::mat4 view){
    GameObject::setView(view);
}

