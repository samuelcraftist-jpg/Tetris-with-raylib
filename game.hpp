#pragma once

#include "grid.hpp"
#include "blocks.hpp"
#include "audio.hpp"

#include <random>
#include <vector>

// The game logic: spawning, movement, rotation, locking, line clearing,
// scoring, level progression, game over, and restart. It owns the grid,
// the active piece, the next piece (preview), and the audio.
class Game {
    public:
    Game();

    // load sounds (must be called after InitAudioDevice)
    void InitAudio();

    void HandleInput();
    void Update();       // automatic falling
    void Draw();         // grid, pieces, panels, text
    bool IsGameOver() const;

    private:
    Grid grid;
    Block currentBlock;  // piece currently falling
    Block nextBlock;     // previewed piece (never touches the grid)
    Audio audio;

    int nextBlockId;     // id of the piece coming after nextBlock
    std::vector<int> bag; // seven-piece bag: ids 1..7, shuffled
    size_t bagIndex;

    std::default_random_engine rng;

    int score;
    int linesCleared;
    int level;

    double fallInterval; // seconds between automatic down steps
    double fallTimer;
    double moveTimer;    // left/right repeat timer

    bool gameOver;

    void Reset();
    void SpawnBag();
    int NextBagId();
    Block MakeBlock(int id);
    void SpawnPiece();
    bool BlockFits(const Block& block) const;
    bool MoveBlock(int dRow, int dColumn);
    void RotateBlock();
    void HardDrop();
    void LockPiece();
    void UpdateFallSpeed();
    void CenterOffset(const Block& block, int& rowOffset, int& colOffset) const;
};
