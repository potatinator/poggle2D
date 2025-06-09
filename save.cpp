#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <glm/glm.hpp>
#include "save.h"
using namespace std;

SaveMgr::SaveMgr() {}

std::vector<Peg*> SaveMgr::load(string fileName, std::vector<Peg*> in){
    string name = "./saves/"+fileName;
    if(!filesystem::exists(name)){
        cout << "couldnt find file";
        return in;
    }
    ifstream f(name);

    string line;
    string out;

    vector<Peg*> genPegs;

    while(getline(f, line)){
        stringstream stream(line);
        vector<string> parts;
        while(getline(stream, out, ' ')){
            parts.push_back(out);
        }
        if(parts.size() >= 2){
            genPegs.push_back(
                new Peg(
                    glm::vec2(
                        stof(parts.at(0)), 
                        stof(parts.at(1))
                    )
                )
            );
        }
    }
    f.close();

    return genPegs;
}
void SaveMgr::save(std::vector<Peg*> pegs){
    string file = "./saves/save0.sav";
    for(int i=0; i<20&&filesystem::exists(file); i++){
        cout << "file: " << file << " already exists, skipping..." << endl;
        file = "./saves/save" + to_string(i) + ".sav";
    }
    cout << "saving to: " << file << endl;
    save(file, pegs);
}
void SaveMgr::save(string name, std::vector<Peg*> pegs){
    ofstream f(name);

    string out;

    for(Peg* p : pegs){
        if(p == nullptr){
            continue;
        }
        out += to_string(p->position.x) + " " + to_string(p->position.y) + "\n";
    }
    f << out;

    f.close();
}