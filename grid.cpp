
#include "grid.hpp"
#include <iostream>
using std::cout;
using std::cin;
Grid::Grid()
{
    rows = 20;
    columns = 10;
    cells = 35;
    init();
};

void Grid::init(){
    // for loop to implement the rows and columns
    for(int row = 0;row < rows; row++)
    {
        for(int column = 0; column < columns; column++)
        {
            grid[row][column] = 0;
        }
    }
};

void Grid::print()
{
    for(int row = 0; row < rows; row++)
    {
        for(int column = 0; column < columns; column++)
        {
            cout << grid[row][column] << " ";
        }
    }
    cout << std::endl;
}