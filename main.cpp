#include "raylib.h"
#include <string> 

struct Ball
{
    float x, y;
    float speedX, speedY;
    float radius;

    void Draw()
    {
        DrawCircle(x, y, radius, WHITE); // center of window, draws from center of circle
    }
};

struct Paddle
{
    float x, y;
    float speed;
    float width, height;
    int score;
    bool flip;

    Rectangle getRect()
    {
        return Rectangle{x - width / 2, y - height / 2, width, height};
    }

    void Draw()
    {
        DrawRectangleRec(getRect(), WHITE);
    }
};

int main()
{
    InitWindow(800, 600, "Pong");
    SetWindowState(FLAG_VSYNC_HINT);

    Ball ball;
    ball.x = GetScreenWidth() / 2;
    ball.y = GetScreenHeight() / 2;
    ball.radius = 5;
    ball.speedX = 300;
    ball.speedY = 300;

    Paddle left;
    left.x = 50;
    left.y = GetScreenHeight() / 2;
    left.width = 10;
    left.height = 100;
    left.speed = 500;
    left.score = 0;
    left.flip = false;

    Paddle right;
    right.x = GetScreenWidth() - 50;
    right.y = GetScreenHeight() / 2;
    right.width = 10;
    right.height = 100;
    right.speed = 500;
    right.score = 0;
    right.flip = false;

    std::string winnerText = "";

    while (!WindowShouldClose())
    {

        ball.x += ball.speedX * GetFrameTime();
        ball.y += ball.speedY * GetFrameTime();
        if (ball.y < 0)
        {
            ball.y = 0;
            ball.speedY *= -1;
        }
        if (ball.y > GetScreenHeight())
        {
            ball.y = GetScreenHeight();
            ball.speedY *= -1;
        }

        if (IsKeyDown(KEY_W))
        {
            left.y -= left.speed * GetFrameTime();
        }
        if (IsKeyDown(KEY_S))
        {
            left.y += left.speed * GetFrameTime();
        }

        if (IsKeyDown(KEY_UP))
        {
            right.y -= right.speed * GetFrameTime();
        }
        if (IsKeyDown(KEY_DOWN))
        {
            right.y += right.speed * GetFrameTime();
        }

        if (left.y + left.height / 2 > GetScreenHeight())
        {
            left.y = GetScreenHeight() - left.height / 2;
        }

        if (right.y + right.height / 2 > GetScreenHeight())
        {
            right.y = GetScreenHeight() - right.height / 2;
        }

        if (left.y - left.height / 2 < 0)
        {
            left.y = left.height / 2;
        }

        if (right.y - right.height / 2 < 0)
        {
            right.y = right.height / 2;
        }

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, right.getRect()))
        {
            if (ball.speedX > 0)
            {
                ball.speedX *= -1.1;
                ball.speedY = (ball.y - right.y) / (right.height / 2) * -ball.speedX;
            }
        }

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, left.getRect()))
        {
            if (ball.speedX < 0)
            {
                ball.speedX *= -1.1;
                ball.speedY = (ball.y - left.y) / (left.height / 2) * ball.speedX;
            }
        }

        if (ball.x < 0 && !right.flip)
        {
            right.score += 1;
            right.flip = true;
            winnerText = "Right Player Wins! \n        " + std::to_string(left.score) + " - " + std::to_string(right.score);
        }

        if (ball.x > GetScreenWidth() && !left.flip)
        {
            left.score += 1;
            left.flip = true;
            winnerText = "Left Player Wins! \n        " + std::to_string(left.score) + " - " + std::to_string(right.score);        
        }

        if (winnerText != "" && IsKeyPressed(KEY_SPACE))
        {
            ball.x = GetScreenWidth() / 2;
            ball.y = GetScreenHeight() / 2;
            ball.speedX = 300;
            ball.speedY = 300;
            winnerText = "";
            left.flip = false;
            right.flip = false;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        ball.Draw();
        left.Draw();
        right.Draw();

        DrawFPS(10, 10);

        if (winnerText != "")
        {
            char* char_array = new char[winnerText.length() + 1];
            char_array[winnerText.length()] = '\0';
            for (int i = 0; i < winnerText.length(); i++) {
                char_array[i] = winnerText[i];
            }
            DrawText(char_array, GetScreenWidth() / 2 - MeasureText(char_array, 48) / 2, GetScreenHeight() / 2, 48, GREEN);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}