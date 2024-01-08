#include "raylib.h"

int main(void) {

    const int screenWidth = 200;
    const int screenHeight = 200;

    InitWindow(screenWidth, screenHeight, "Template");
    HideCursor();

    Texture2D tardigradeTexture = LoadTexture("assets/graphics/tardigrade.png");
    float tardigradeXPos = 0;

    Texture2D cursorTexture = LoadTexture("assets/graphics/fish_food_cursor.png");

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        tardigradeXPos += GetFrameTime() * 10.0f;

        BeginDrawing();

        ClearBackground(BLACK);
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