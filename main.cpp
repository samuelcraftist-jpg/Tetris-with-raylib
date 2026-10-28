// learning raylib with this project
//
// Tetris: a grid (20 rows x 10 columns), falling tetrominoes, line clearing,
// score, level, next-piece preview, game over and restart.
//
// Build with the VS Code "build" task (g++, C++17, raylib).

#include <raylib.h>
#include "constants.hpp"
#include "colors.hpp"
#include "game.hpp"

int main()
{
    // initializes the game window
    InitWindow(WindowWidth, WindowHeight, "Tetris");
    SetTargetFPS(60); // how fast the game runs (60 frames per second)

    // audio must be initialized before sounds or music are loaded
    InitAudioDevice();

    {
        Game game;
        game.InitAudio(); // load sound effects and music

        // my game loop
        while (!WindowShouldClose())
        {
            game.HandleInput(); // player input
            game.Update();      // automatic falling and locking

            BeginDrawing(); // start drawing the frame
            ClearBackground(abyss);
            game.Draw();      // grid, pieces, panels, text
            EndDrawing();     // show the frame
        }

        // game goes out of scope here: all sounds and music are unloaded
        // before we close the audio device below
    }

    CloseAudioDevice();
    CloseWindow(); // closes the window cleanly
}

