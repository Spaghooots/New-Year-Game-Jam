#include "raylib.h"

int main(void) {

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Template");

    Texture2D fish = LoadTexture("assets/graphics/temp_fish.png");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexture(fish, 100, 100, WHITE);
        DrawText("balls", 190, 200, 20, LIGHTGRAY);

        EndDrawing();

    }

    UnloadTexture(fish);
    CloseWindow();

    return 0;
}