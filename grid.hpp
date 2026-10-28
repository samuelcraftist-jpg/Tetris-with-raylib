#pragma once // Used to avoid repetitive headers

#include <raylib.h>
#include <vector>

#include "constants.hpp"

// creating a class
class Grid {
    public:
    Grid();
    void Draw();
    void init();
    void print();
    int grid[GridRows][GridColumns];

    int rows;
    int columns;
    int cellSize; // size of one cell in pixels

    // checks
    bool IsInside(int row, int column) const;
    bool IsEmpty(int row, int column) const;
    bool IsRowFull(int row) const;

    // line clearing: returns how many rows were cleared
    int ClearFullRows();

    private:
    void RemoveRow(int row);

    std::vector<Color> Colors;
};