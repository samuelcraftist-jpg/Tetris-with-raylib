// learning raylib with this project

/* 
<---------------------------------------------------------------------------->
NOTES: Tetris contains 20 rows and 10 columns.
1. InItWindow(x, y, "A title parameter")
2. SetTargetFPS() Function
3. A while loop that keeps the window open till the while toop condition becomes true.
 !WindowshouldClose() makes the condition false. Once we lick close it becomes true then the game loop ends.
<----------------------------------------------------------------------------->
CODE:
*/
#include <raylib.h> // Main raylib header file ig
#include "grid.hpp"

#include <iostream>

using std::cout; // i used them directly because i dont wanna write std::cout thing everytime "-"
using std::cin; // same applies

int main(){

    // initializes the game window
    InitWindow(300, 400,"Tetris ");
    SetTargetFPS(60); // setting up how fast my game should run

    Grid grid = Grid();
    grid.print();

    // My game loop
    while(!WindowShouldClose())
    {
        BeginDrawing(); // begin drawing function draws the contents
        ClearBackground(BLACK);
        EndDrawing(); // ends the drawing
    }
    CloseWindow(); // closes the window cleanly or ends the program
    cout<<"Window has closed.";
}