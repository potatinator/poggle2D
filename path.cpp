#include "path.h"


Path::Path(glm::vec2 pos, glm::vec2 scale, int layer)
    : GameObject(pos, scale, layer, angle, std::make_shared<Shader>("./shaders/main.vert", "./shaders/pathOld.frag")), vel(0.01, 0), pos(0, 0) {

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

}
void Path::update(float dt){
    GameObject::update(dt);
}
void Path::draw(){
    shader->use();
    shader->setVec2("u_resolution", glm::vec2(800, 600));
    shader->setVec2("u_x0", pos);
    shader->setVec2("u_v0", vel * glm::vec2(-1, 1));
    shader->setFloat("u_g", 500.0);
    shader->setMat4("transform", this->transform);
    shader->setInt("layer", -layer);
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, ((sizeof(vertices)/sizeof(float))/4.0));
    glBindVertexArray(0);
}
void Path::setView(glm::mat4 view){
    GameObject::setView(view);
}

