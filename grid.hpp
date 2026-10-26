// I need to create a headers for the grids 
#pragma once // Used to avoid repeative headers

// creating a class
class Grid {
    public:
    Grid();
    void init();
    void print();
    int grid[20][10];

    private:
    int rows;
    int columns;
    int cells;
};