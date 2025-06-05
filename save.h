#ifndef SAVE_H
#define SAVE_H
#include <fstream>
#include <glm/glm.hpp>
#include "peg.h"
using namespace std;

class SaveMgr{
    public:
        SaveMgr();
        void save(string file, std::vector<Peg*> pegs = std::vector<Peg*>());
        void save(std::vector<Peg*> pegs);
        std::vector<Peg*> load(string file, std::vector<Peg*> in);
};
#endif