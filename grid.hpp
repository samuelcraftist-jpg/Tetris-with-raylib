// I need to create a headers for the grids
#pragma once // Used to avoid repeative headers

#include <raylib.h>
#include <vector>

// creating a class
class Grid {
    public:
    Grid();
    void Draw();
    void init();
    void print();
    int grid[20][10];

    private:
    int rows;
    int columns;
    int cells;

    std::vector<Color>Colors;
};