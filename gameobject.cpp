
#include "gameobject.h"

GameObject::GameObject(){}
GameObject::GameObject(glm::vec2 pos, glm::vec2 scale, int layer, float angle, std::shared_ptr<Shader> shader)
    : position(pos), scale(scale), angle(angle), shader(shader), layer(layer) {
    
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
void GameObject::update(float dt){
    transform = glm::mat4(1.0);
    transform = glm::translate(transform, glm::vec3(this->position, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)
    transform = glm::translate(transform, glm::vec3(0.5f * this->scale.x, 0.5f * this->scale.y, 0.0f)); // move origin of rotation to center of quad
    transform = glm::rotate(transform, glm::radians(this->angle), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    transform = glm::translate(transform, glm::vec3(-0.5f * this->scale.x, -0.5f * this->scale.y, 0.0f)); // move origin back
    transform = glm::scale(transform, glm::vec3(this->scale*glm::vec2(1.0, -1.0), 1.0f)); // last scale

}
void GameObject::draw() {
    shader->use();
    shader->setMat4("transform", this->transform);
    shader->setInt("layer", -layer);
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
void GameObject::setView(glm::mat4 view){
    shader->use();
    shader->setMat4("view", view);
}
void GameObject::setDebug(bool debug){
    shader->use();
    shader->setBool("debug", debug);
}

TexturedGameObject::TexturedGameObject(glm::vec2 pos, Texture2D tex, glm::vec2 scale, int layer, float angle)
    : GameObject(pos, scale, layer, angle, std::make_shared<Shader>("./shaders/main.vert", "./shaders/texture.frag")), texture(tex) {

}
void TexturedGameObject::update(float dt){
    GameObject::update(dt);
}
void TexturedGameObject::draw(){
    shader->use();
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();
    shader->setInt("tex", 0);
    GameObject::draw();
}
void TexturedGameObject::setView(glm::mat4 view){
    GameObject::setView(view);
}

ColoredGameObject::ColoredGameObject(glm::vec2 pos, glm::vec3 col, glm::vec2 scale, int layer, float angle)
    : GameObject(pos, scale, layer, angle, std::make_shared<Shader>("./shaders/main.vert", "./shaders/color.frag")), color(col) {
        
}
void ColoredGameObject::update(float dt){
    GameObject::update(dt);
}
void ColoredGameObject::draw(){
    shader->use();
    shader->setVec3("color", this->color);
    GameObject::draw();
}
void ColoredGameObject::setView(glm::mat4 view){
    GameObject::setView(view);
}

