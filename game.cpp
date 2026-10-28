#include "game.hpp"

#include <algorithm>
#include <random>

// Scoring for clearing 1, 2, 3, or 4 lines at once (multiplied by level)
const int ScoreTable[5] = { 0, 100, 300, 500, 800 };

// Timing
const double StartFallInterval = 0.50;  
const double MinFallInterval = 0.05;    // never fall faster than this
const double LevelSpeedDecrease = 0.05; // seconds faster per level
const double SoftDropInterval = 0.05;  
const double SideMoveDelay = 0.10;      

Game::Game()
    : rng(20261028u) 
{
    Reset();
}

void Game::InitAudio()
{
    audio.Init();
}

void Game::Reset()
{
    grid.init();

    score = 0;
    linesCleared = 0;
    level = 1;
    fallTimer = 0;
    moveTimer = 0;
    gameOver = false;

    UpdateFallSpeed();
    SpawnBag();

    // prepare the preview piece
    nextBlockId = NextBagId();
    nextBlock = MakeBlock(nextBlockId);

    SpawnPiece();
}

void Game::SpawnBag()
{
    bag = { 1, 2, 3, 4, 5, 6, 7 };
    std::shuffle(bag.begin(), bag.end(), rng);
    bagIndex = 0;
}

int Game::NextBagId()
{
    if (bagIndex >= bag.size())
    {
        SpawnBag();
    }
    return bag[bagIndex++];
}

Block Game::MakeBlock(int id)
{
    switch (id)
    {
        case 1: return LBlock();
        case 2: return IBlock();
        case 3: return OBlock();
        case 4: return TBlock();
        case 5: return SBlock();
        case 6: return ZBlock();
        case 7: return JBlock();
        default: return OBlock();
    }
}

void Game::SpawnPiece()
{
    // move the previewed piece into play and draw a new next piece
    currentBlock = MakeBlock(nextBlockId);
    currentBlock.Move(0, 3); // appear at the top, roughly centered

    nextBlockId = NextBagId();
    nextBlock = MakeBlock(nextBlockId);

    if (!BlockFits(currentBlock))
    {
        gameOver = true;
        audio.PlayGameOverSound();
        audio.PauseMusic();
    }
}

bool Game::BlockFits(const Block& block) const
{
    std::vector<Position> tiles = block.GetCurrentCells();
    for (Position p : tiles)
    {
        if (!grid.IsInside(p.row, p.column))
        {
            return false; // outside the grid
        }
        if (!grid.IsEmpty(p.row, p.column))
        {
            return false; // cell already occupied by a locked piece
        }
    }
    return true;
}

bool Game::MoveBlock(int dRow, int dColumn)
{
    currentBlock.Move(dRow, dColumn);
    if (!BlockFits(currentBlock))
    {
        currentBlock.Move(-dRow, -dColumn); // put it back where it was
        return false;
    }
    return true;
}

void Game::RotateBlock()
{
    currentBlock.Rotate(1); // try clockwise
    if (!BlockFits(currentBlock))
    {
        currentBlock.Rotate(-1); // blocked: restore previous rotation
    }
}

void Game::HardDrop()
{
    int rowsDropped = 0;
    while (MoveBlock(1, 0))
    {
        rowsDropped++;
    }
    score += rowsDropped * 2; // small reward for dropping fast
    LockPiece();
}

void Game::LockPiece()
{
    // write the active piece into the grid
    std::vector<Position> tiles = currentBlock.GetCurrentCells();
    for (Position p : tiles)
    {
        if (grid.IsInside(p.row, p.column))
        {
            grid.grid[p.row][p.column] = currentBlock.id;
        }
    }

    int cleared = grid.ClearFullRows();
    if (cleared > 0)
    {
        linesCleared += cleared;
        score += ScoreTable[cleared] * level;

        int newLevel = linesCleared / 10 + 1;
        if (newLevel > level)
        {
            level = newLevel;
            UpdateFallSpeed();
            audio.PlayLevelUpSound();
        }
        audio.PlayLineClearSound();
    }
    else
    {
        audio.PlayLockSound();
    }

    SpawnPiece();
}

void Game::UpdateFallSpeed()
{
    fallInterval = StartFallInterval - (level - 1) * LevelSpeedDecrease;
    if (fallInterval < MinFallInterval)
    {
        fallInterval = MinFallInterval;
    }
}

void Game::CenterOffset(const Block& block, int& rowOffset, int& colOffset) const
{
    std::vector<Position> tiles = block.GetCurrentCells();

    int minRow = tiles[0].row;
    int maxRow = tiles[0].row;
    int minCol = tiles[0].column;
    int maxCol = tiles[0].column;

    for (Position p : tiles)
    {
        if (p.row < minRow) minRow = p.row;
        if (p.row > maxRow) maxRow = p.row;
        if (p.column < minCol) minCol = p.column;
        if (p.column > maxCol) maxCol = p.column;
    }

    // the preview box is 4 x 4 cells, whose center is cell index 2
    rowOffset = 2 - (minRow + maxRow) / 2;
    colOffset = 2 - (minCol + maxCol) / 2;
}

void Game::HandleInput()
{
    audio.Update(); // keep the background music stream alive

    if (gameOver)
    {
        if (IsKeyPressed(KEY_R))
        {
            audio.PlayRestartSound();
            audio.ResumeMusic();
            Reset();
        }
        return;
    }

    // independent toggles
    if (IsKeyPressed(KEY_M))
    {
        audio.ToggleMusic();
    }
    if (IsKeyPressed(KEY_S))
    {
        audio.ToggleSounds();
    }

    // left / right (immediate on first press, then repeat)
    bool leftHeld = IsKeyDown(KEY_LEFT);
    bool rightHeld = IsKeyDown(KEY_RIGHT);
    if (leftHeld || rightHeld)
    {
        moveTimer += GetFrameTime();
        bool justPressed = IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT);
        if (justPressed || moveTimer >= SideMoveDelay)
        {
            int direction = leftHeld ? -1 : 1;
            if (MoveBlock(0, direction))
            {
                audio.PlayMoveSound();
            }
            moveTimer = 0;
        }
    }
    else
    {
        moveTimer = 0;
    }

    // rotate
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_X))
    {
        RotateBlock();
        audio.PlayRotateSound();
    }

    // soft drop
    if (IsKeyPressed(KEY_DOWN))
    {
        audio.PlaySoftDropSound();
    }

    // hard drop
    if (IsKeyPressed(KEY_SPACE))
    {
        HardDrop();
        audio.PlayHardDropSound();
    }
}

void Game::Update()
{
    if (gameOver)
    {
        return;
    }

    double dt = GetFrameTime();
    double interval = IsKeyDown(KEY_DOWN) ? SoftDropInterval : fallInterval;

    fallTimer += dt;
    if (fallTimer >= interval)
    {
        fallTimer = 0;
        if (!MoveBlock(1, 0))
        {
            LockPiece();
        }
    }
}

void Game::Draw()
{
    grid.Draw();

    // draw a border around the play area
    DrawRectangleLines(0, 0, GridColumns * CellSize, GridRows * CellSize, WHITE);

    // active piece: white outline keeps it visually distinct from locked pieces
    std::vector<Position> tiles = currentBlock.GetCurrentCells();
    for (Position p : tiles)
    {
        DrawRectangleLines(
            p.column * CellSize,
            p.row * CellSize,
            CellSize,
            CellSize,
            WHITE);
    }
    currentBlock.Draw();

    // ---------- side panel ----------
    Color panelBg = { 25, 30, 45, 255 };
    DrawRectangle(PanelLeft, 0, PanelWidth, WindowHeight, panelBg);
    DrawRectangleLines(PanelLeft, 0, 1, WindowHeight, WHITE);

    DrawText("NEXT", PreviewBoxLeft, 25, 20, WHITE);
    DrawRectangleLines(PreviewBoxLeft, PreviewBoxTop, PreviewBoxSize, PreviewBoxSize, WHITE);

    // center the preview piece inside its 4 x 4 cell box
    int rowOffset = 0;
    int colOffset = 0;
    CenterOffset(nextBlock, rowOffset, colOffset);
    nextBlock.Draw(
        PreviewBoxLeft + 1 + colOffset * CellSize,
        PreviewBoxTop + 1 + rowOffset * CellSize);

    DrawText(TextFormat("SCORE %d", score), PreviewBoxLeft, 200, 20, WHITE);
    DrawText(TextFormat("LEVEL %d", level), PreviewBoxLeft, 240, 20, WHITE);
    DrawText(TextFormat("LINES %d", linesCleared), PreviewBoxLeft, 280, 20, WHITE);

    DrawText("CONTROLS", PreviewBoxLeft, 340, 20, WHITE);
    DrawText("Left/Right: move", PreviewBoxLeft, 365, 15, LIGHTGRAY);
    DrawText("Up / X: rotate", PreviewBoxLeft, 382, 15, LIGHTGRAY);
    DrawText("Down: soft drop", PreviewBoxLeft, 399, 15, LIGHTGRAY);
    DrawText("Space: hard drop", PreviewBoxLeft, 416, 15, LIGHTGRAY);
    DrawText("M: music  S: sound", PreviewBoxLeft, 433, 15, LIGHTGRAY);
    DrawText("R: restart", PreviewBoxLeft, 450, 15, LIGHTGRAY);

    if (gameOver)
    {
        // dimmed overlay
        DrawRectangle(0, 0, WindowWidth, WindowHeight, { 0, 0, 0, 170 });

        const char* overMsg = "GAME OVER";
        int overWidth = MeasureText(overMsg, 30);
        DrawText(overMsg, (WindowWidth - overWidth) / 2, 300, 30, RED);

        const char* hintMsg = "Press R to restart";
        int hintWidth = MeasureText(hintMsg, 20);
        DrawText(hintMsg, (WindowWidth - hintWidth) / 2, 345, 20, WHITE);
    }
}

bool Game::IsGameOver() const
{
    return gameOver;
}
