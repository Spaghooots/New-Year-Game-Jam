#include "raylib.h"

int main(void) {

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Template");

    Texture2D tardigradeTexture = LoadTexture("assets/graphics/tardigrade.png");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexture(tardigradeTexture, 100, 100, WHITE);
        DrawText("balls", 190, 200, 20, LIGHTGRAY);

        EndDrawing();

    }

    UnloadTexture(tardigradeTexture);
    CloseWindow();

    return 0;
}