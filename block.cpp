#include "block.hpp"

Block::Block()
{
    cellSize = CellSize;
    rotationState = 0;
    colors = getCellColors();
}

void Block::Draw()
{
    Draw(0, 0);
}

void Block::Draw(int offsetX, int offsetY)
{
    std::vector<Position> tiles = cells[rotationState];
    for (Position item : tiles)
    {
        DrawRectangle(
            item.column * cellSize + 1 + offsetX,
            item.row * cellSize + 1 + offsetY,
            cellSize - 1,
            cellSize - 1,
            colors[id]);
    }
}

void Block::Move(int dRow, int dColumn)
{
    // move every cell of every rotation state so the piece stays consistent
    for (auto& pair : cells)
    {
        std::vector<Position>& tiles = pair.second;
        for (Position& item : tiles)
        {
            item.row += dRow;
            item.column += dColumn;
        }
    }
}

void Block::Rotate(int direction)
{
    rotationState = (rotationState + direction + 4) % 4;
}

int Block::GetRotationState() const
{
    return rotationState;
}

std::vector<Position> Block::GetCurrentCells() const
{
    return cells.at(rotationState); // .at() fails loudly if a rotation state is missing
}