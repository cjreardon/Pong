#include "raylib.h"

int main() {
    InitWindow(800, 600, "Pong");
    SetWindowState(FLAG_VSYNC_HINT);
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);

            DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, 5, WHITE); //center of window, draws from center of circle
            DrawRectangle(50, GetScreenHeight() / 2 - 50, 10, 100, WHITE); //left paddle, draws from top left of rectangle
            DrawRectangle(GetScreenWidth() - 50 - 10, GetScreenHeight() / 2 - 50, 10, 100, WHITE); //right paddle, draws from top left of rectangle
            
            
            DrawFPS(10,10);
        EndDrawing();
    }
    

    CloseWindow();
    return 0;
}