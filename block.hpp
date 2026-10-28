#pragma once

#include "position.hpp"
#include "constants.hpp"
#include <map>
#include <vector>
#include "colors.hpp"

class Block 
{
    public:
    Block();
    int id;
    std::map<int, std::vector<Position>>cells;

    // drawing
    void Draw();                                       // draws at the piece's own cell coordinates
    void Draw(int offsetX, int offsetY);               // draws shifted by offsetX/offsetY pixels (used for the NEXT preview)

    // movement and rotation: all rotation states move together
    void Move(int dRow, int dColumn);
    void Rotate(int direction);                        // +1 = clockwise, -1 = counter-clockwise

    int GetRotationState() const;
    std::vector<Position> GetCurrentCells() const;     // cells of the current rotation state

    private:
    int cellSize;
    int rotationState;
    std::vector<Color> colors;
};
