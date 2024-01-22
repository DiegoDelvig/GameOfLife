#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <time.h>
#include <unistd.h>


// Delcare global functions
void createRandomGrid(int COLS, int ROWS, int grid[ROWS][COLS]);
void drawArr(int COLS, int ROWS);
void drawCells(int COLS, int ROWS, int grid[ROWS][COLS]);
void setArray(int value, int COLS, int ROWS, int arr[ROWS][COLS]);

// Declare global variables
int cellSize = 5;
int COLS;
int ROWS;


int main(void)
{
    InitWindow(1000, 800, "Game of Life");
    SetTargetFPS(60);
    ROWS = GetScreenHeight() / cellSize;
    COLS = (GetScreenWidth() - 200) / cellSize;

    int grid[ROWS][COLS];
    createRandomGrid(COLS, ROWS, grid);

    int nextGrid[ROWS][COLS];
    setArray(0, COLS, ROWS, nextGrid);

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SPACE))
        {
            createRandomGrid(COLS, ROWS, grid);
        }

        BeginDrawing();

        ClearBackground(WHITE);
        drawCells(COLS, ROWS, grid);
        // drawArr(COLS, ROWS);
        // Draw Separation
        DrawLine(GetScreenWidth() - 200, 0, GetScreenWidth() - 200, GetScreenHeight(), BLACK);

        EndDrawing();

        // Logic
        int count = 0;
        for (int i = 0; i < COLS; ++i)
        {
            for (int j = 0; j < ROWS; ++j)
            {
                count = 0;
                if (!(i==0 || j==0 || i==COLS-1 || j==ROWS-1))
                {
                    if (grid[i-1][j-1] == 1) { count++; }
                    if (grid[i-1][j] == 1) { count++; }
                    if (grid[i-1][j+1] == 1) { count++; }
                    if (grid[i][j-1] == 1) { count++; }
                    if (grid[i][j+1] == 1) { count++; }
                    if (grid[i+1][j-1] == 1) { count++; }
                    if (grid[i+1][j] == 1) { count++; }
                    if (grid[i+1][j+1] == 1) { count++; }

                    if (grid[i][j] == 1)
                    {
                        if (count < 2) { nextGrid[i][j] = 0; }
                        if (count > 3) { nextGrid[i][j] = 0; }
                        if (count == 2) { nextGrid[i][j] = 1; }
                        if (count == 3) { nextGrid[i][j] = 1; }
                    }
                    else if (grid[i][j] == 0)
                    {
                        if (count == 3) { nextGrid[i][j] = 1; }
                    }
                }
                else { nextGrid[i][j] = 0; }
            }
        }


        for (int i = 0; i < COLS; ++i)
        {
            for (int j = 0; j < ROWS; ++j)
            {
                grid[i][j] = nextGrid[i][j];
            }
        }
        sleep(0.5);
    }

    CloseWindow();
    return 0;
}

void setArray(int value, int COLS, int ROWS, int arr[ROWS][COLS])
{
    for (int i = 0; i < COLS; ++i)
    {
        for (int j = 0; j < 0; ++j)
        {
           arr[i][j] = value;
        }
    }
}

void createRandomGrid(int COLS, int ROWS, int grid[ROWS][COLS])
{

    srand((unsigned int) time(NULL));
    for (int i = 0; i < COLS; ++i)
    {
        for (int j = 0; j < ROWS; ++j)
        {
            float rnd = ((float) rand() / (float)(RAND_MAX));
            if (rnd > 0.50){
              grid[i][j] = 1;
            } else {
                grid[i][j] = 0;
            }
        }
    }
}

void drawArr(int COLS, int ROWS)
{
    // Draw verticals lines of the grids
    for (int i = 0; i < COLS; ++i)
    {
        DrawLine(i*cellSize, 0, i*cellSize, GetScreenHeight(), BLACK);
    }
    // Draw horizontal lines of the grids
    for (int j = 0; j < ROWS; ++j)
    {
        DrawLine(0, j*cellSize, GetScreenWidth(), j*cellSize, BLACK);
    }
}

void drawCells(int COLS, int ROWS, int arr[ROWS][COLS])
{
    for (int i = 0; i < COLS; ++i)
    {
        for (int j = 0; j < ROWS; ++j)
        {
            if (arr[i][j] == 1)
            {
                DrawRectangle(i*cellSize, j*cellSize, cellSize, cellSize, BLACK);
            }
            if (arr[i][j] == 0)
            {
                DrawRectangle(i*cellSize, j*cellSize, cellSize, cellSize, WHITE);
            }
        }
    }
}
