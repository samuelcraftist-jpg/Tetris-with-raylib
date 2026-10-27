
#include "grid.hpp"
#include <iostream>

using std::cout;

Grid::Grid()
{
    rows = 20;
    columns = 10;
    cells = 35;
    Colors = getCellColors();
    init();
};

void Grid::init()
{
    // for loop to implement the rows and columns
    for (int row = 0; row < rows; row++)
    {
        for (int column = 0; column < columns; column++)
        {
            grid[row][column] = 0;
        }
    }
};

void Grid::print()
{
    for (int row = 0; row < rows; row++)
    {
        for (int column = 0; column < columns; column++)
        {
            cout << grid[row][column] << " ";
        }
        cout << std::endl;
    }
}

std::vector<Color> Grid::getCellColors()
{
    return {
        {11, 16, 38, 255},    // Abyss color for back ground
        {255, 0, 0, 255},     // Red
        {0, 0, 255, 255},     // Blue
        {255, 255, 0, 255},   // Yellow
        {255, 255, 255, 255}, // White
        {0, 255, 0, 255},     // green
        {128, 0, 128, 255},   // Purple
        {255, 165, 0, 255}    // Orange
    };
}

void Grid::Draw()
{
    for (int row = 0; row < rows; row++)
    {
        for (int column = 0; column < columns; column++)
        {
            int cellVal = grid[row][column];

            DrawRectangle(
                column * cells + 1,
                row * cells + 1,
                cells - 1,
                cells - 1,
                Colors[cellVal]);
        }
    }
}
