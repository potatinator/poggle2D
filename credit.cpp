#include "credit.h"
#include <iostream>

// ifstream file;
// int line;
// std::vector<TextRenderer> texts;
// Shader shader;
// float speed = 25.0f;
Credit::Credit (std::string fileName) : line(0), file(std::ifstream(fileName)), text(TextRenderer(800, 600)){}

void Credit::init(){
    this->text.Load("./resources/font2.ttf", 24);

    std::string line;
    while(getline(file, line)){
        out += line + "\n";
    }
}
void Credit::start(){

}
void Credit::stop(){

    std::cout << "credits stop" << std::endl;
}
void Credit::update(float dt){
    pos -= speed*dt;
}
void Credit::draw(){
    text.RenderText(out, 50.0, pos, 1.0);
}
void Credit::setView(glm::mat4 view){

}