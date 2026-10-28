#include "grid.hpp"
#include <iostream>
#include "colors.hpp"

using std::cout;

Grid::Grid()
{
    rows = GridRows;
    columns = GridColumns;
    cellSize = CellSize;
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

bool Grid::IsInside(int row, int column) const
{
    return row >= 0 && row < rows && column >= 0 && column < columns;
}

bool Grid::IsEmpty(int row, int column) const
{
    return grid[row][column] == 0;
}

bool Grid::IsRowFull(int row) const
{
    for (int column = 0; column < columns; column++)
    {
        if (grid[row][column] == 0)
        {
            return false;
        }
    }
    return true;
}

int Grid::ClearFullRows()
{
    int cleared = 0;

    // go from bottom to top so rows above can fall down safely
    for (int row = rows - 1; row >= 0; row--)
    {
        while (IsRowFull(row))
        {
            RemoveRow(row);
            cleared++;
        }
    }

    return cleared;
}

void Grid::RemoveRow(int row)
{
    // every row above moves down by one
    for (int r = row; r > 0; r--)
    {
        for (int column = 0; column < columns; column++)
        {
            grid[r][column] = grid[r - 1][column];
        }
    }
    // a new empty row appears at the top
    for (int column = 0; column < columns; column++)
    {
        grid[0][column] = 0;
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
                column * cellSize + 1,
                row * cellSize + 1,
                cellSize - 1,
                cellSize - 1,
                Colors[cellVal]);
        }
    }
}
