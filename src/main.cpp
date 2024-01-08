#include "raylib.h"
#include "fish.h"
#include <iostream>

int main(void) {

    const int screenWidth = 400;
    const int screenHeight = 400;

    InitWindow(screenWidth, screenHeight, "Template");

    Texture2D tardigradeTexture = LoadTexture("assets/graphics/tardigrade.png");

    SetTargetFPS(60);

    Vector2 mousePosition{1, 0};

    Fish LeFish = Fish(tardigradeTexture, Vector2{screenWidth/2, screenHeight/2}, mousePosition);

    while (!WindowShouldClose()) {

        SetWindowSize(GetScreenWidth(), GetScreenHeight());

        mousePosition = GetMousePosition();

        std::cout << mousePosition.y;

        LeFish.Update();

        BeginDrawing();
        

        ClearBackground(BLACK);

        LeFish.Draw();
        DrawTexture(tardigradeTexture, 0, 0, WHITE);
        DrawText("balls", 0, 0, 20, LIGHTGRAY);

        EndDrawing();

    }

    UnloadTexture(tardigradeTexture);
    CloseWindow();

    return 0;
}