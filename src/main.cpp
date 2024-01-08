#include "raylib.h"

int main(void) {

    const int screenWidth = 200;
    const int screenHeight = 200;

    InitWindow(screenWidth, screenHeight, "Template");

    Texture2D tardigradeTexture = LoadTexture("assets/graphics/tardigrade.png");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        BeginDrawing();

        ClearBackground(BLACK);
        DrawTexture(tardigradeTexture, 0, 0, WHITE);
        DrawText("balls", 0, 0, 20, LIGHTGRAY);

        EndDrawing();

    }

    UnloadTexture(tardigradeTexture);
    CloseWindow();

    return 0;
}