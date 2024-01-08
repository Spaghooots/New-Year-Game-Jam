#include "raylib.h"
#include "fish.h"
#include <iostream>

int main(void) {

    const int screenWidth = 400;
    const int screenHeight = 400;

    InitWindow(screenWidth, screenHeight, "Template");
    HideCursor();

    Texture2D tardigradeTexture = LoadTexture("assets/graphics/tardigrade.png");
    float tardigradeXPos = 0;

    Texture2D cursorTexture = LoadTexture("assets/graphics/fish_food_cursor.png");

    SetTargetFPS(60);

    Vector2 mousePosition{1, 0};

    Fish LeFish = Fish(tardigradeTexture, Vector2{screenWidth/2, screenHeight/2}, mousePosition);
    while (!WindowShouldClose()) {

        SetWindowSize(GetScreenWidth(), GetScreenHeight());

        mousePosition = GetMousePosition();

        std::cout << mousePosition.y;

        LeFish.Update();
        tardigradeXPos += GetFrameTime() * 10.0f;

        BeginDrawing();
        

        ClearBackground(BLACK);

        LeFish.Draw();
        DrawTexture(tardigradeTexture, tardigradeXPos, 0, WHITE);
        DrawTexture(cursorTexture, GetMousePosition().x, GetMousePosition().y, WHITE);
        DrawText("balls", 0, 0, 20, LIGHTGRAY);

        EndDrawing();

    }

    UnloadTexture(tardigradeTexture);
    UnloadTexture(cursorTexture);
    CloseWindow();

    return 0;
}