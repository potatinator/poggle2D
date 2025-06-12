#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <glm/glm.hpp>
using namespace std;

void save(vector<glm::vec2> pegs);
void save(string name, vector<glm::vec2> pegs);

int main(){
    vector<glm::vec2> pegs;

    int p = 20;
    float len = 800/p;

    for(int j=0; j<2; j++){
    for(int i=-1; i<p; i++){
        pegs.push_back(glm::vec2(i*len+(j*5), (400-(50*j))+(40*(1/cos((i*len+(j*5))*0.05)))));
    }
    }
    for(int i=0; i<pegs.size(); i++){
        if(pegs[i].x < 0 || pegs[i].x > 790){
            pegs.erase(pegs.begin()+i);
        }
    }
    save(pegs);
}

void save(vector<glm::vec2> pegs){
    string file = "./saves/save0.sav";
    for(int i=0; i<20&&filesystem::exists(file); i++){
        cout << "file: " << file << " already exists, skipping..." << endl;
        file = "./saves/save" + to_string(i) + ".sav";
    }
    cout << "saving to: " << file << endl;
    save(file, pegs);
}
void save(string name, vector<glm::vec2> pegs){
    ofstream f(name);

    string out;

    for(glm::vec2 p : pegs){
        out += to_string(p.x) + " " + to_string(p.y) + "\n";
    }
    f << out;

    f.close();
}