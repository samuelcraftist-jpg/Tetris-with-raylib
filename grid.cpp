
#include "grid.hpp"
#include <iostream>
#include "colors.hpp"

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
