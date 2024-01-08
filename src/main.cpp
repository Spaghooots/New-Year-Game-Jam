#include "raylib.h"
#include "fish.h"


int main(void) {

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Template");


    Texture2D tardigradeTexture = LoadTexture("assets/graphics/tardigrade.png");
    float tardigradeXPos = 0;

    Texture2D cursorTexture = LoadTexture("assets/graphics/fish_food_cursor.png");
    
    SetTargetFPS(60);

    Fish headFish = Fish(tardigradeTexture, Vector2{screenWidth/2, screenHeight/2});
    while (!WindowShouldClose()) {

        SetWindowSize(fmin(GetScreenWidth(), screenWidth), fmin(GetScreenHeight(), screenHeight));
        
        headFish.Update(GetMousePosition());

        tardigradeXPos += GetFrameTime() * 10.0f;

        BeginDrawing();
        

        ClearBackground(BLUE);

        headFish.Draw();

        DrawTexture(tardigradeTexture, tardigradeXPos, 0, WHITE);
        DrawTexture(cursorTexture, GetMousePosition().x, GetMousePosition().y, WHITE);

        EndDrawing();

    }

    UnloadTexture(tardigradeTexture);
    UnloadTexture(cursorTexture);
    CloseWindow();

    return 0;
}