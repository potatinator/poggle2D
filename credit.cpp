#include "credit.h"
#include <iostream>
#include <bits/stdc++.h>
#include <vector>

// ifstream file;
// int line;
// std::vector<TextRenderer> texts;
// Shader shader;
// float speed = 25.0f;
Credit::Credit (std::string fileName) : line(0), file(std::ifstream(fileName)), text(TextRenderer(800, 600)), text2(TextRenderer(800, 600)){}

void Credit::init(){
    this->text.Load("./resources/font2.ttf", 24);
    this->text2.Load("./resources/font2.ttf", 24);

    std::string line;
    std::string l;
    while(getline(file, line)){
        std::stringstream stream(line);
        std::vector<std::string> parts;
        while(getline(stream, l, ':')){
            parts.push_back(l);
        }
        if(parts.size() >= 2){
            outn += parts.at(0) + "\n";
            out += parts.at(1) + "\n";
            outc += "\n";
        } else if(parts.size() == 1){
            outc += parts.at(0) + "\n";
            out += "\n";
            outn += "\n";
        } else {
            outc += "\n";
            out += "\n";
            outn += "\n";
        }
    }
}
void Credit::start(){
    running = true;
    pos = 600.0f;
}
void Credit::stop(){

    std::cout << "credits stop" << std::endl;
    running = false;
}
void Credit::update(float dt){
    if(running){
        pos -= speed*dt;
    }
}
void Credit::draw(){
    text.RenderText(out, 410.0, pos, 1.0);
    text.RenderTextRight(outn, 390.0, pos, 1.0);
    text.RenderTextCentered(outc, 400.0, pos, 1.0);
}
void Credit::setView(glm::mat4 view){

}