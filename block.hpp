#pragma once

#include "position.hpp"
#include <map>
#include <vector>
#include "colors.hpp"

class Block 
{
    public:
    Block();
    int id;
    std::map<int, std::vector<Position>>cells;
    void Draw();

    private:
    int cellSize;
    int rotationState;
    std::vector<Color> colors;
};
