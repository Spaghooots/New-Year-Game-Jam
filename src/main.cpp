#include <iostream>
#include "raylib.h"
#include "fish.h"


int main(void) {

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Template");

    Texture2D tardigradeTexture = LoadTexture("assets/graphics/tardigrade.png");
    Texture2D cursorTexture = LoadTexture("assets/graphics/fish_food_cursor.png");
    
    // All my fishies :)
    Fish headFish = Fish(tardigradeTexture, Vector2{screenWidth/2, screenHeight/2}, 2);
    Fish Fishron = Fish(tardigradeTexture, Vector2{screenWidth/2, screenHeight/2}, 10);
    Fish LeFishe = Fish(tardigradeTexture, Vector2{screenWidth/2, screenHeight/2}, 10);
    Fish Terry = Fish(tardigradeTexture, Vector2{screenWidth/2, screenHeight/2}, 10);

    int waterLevelStartY = 50;

    SetTargetFPS(60);
    while (!WindowShouldClose()) {

        SetWindowSize(fmin(GetScreenWidth(), screenWidth), fmin(GetScreenHeight(), screenHeight));
        
        headFish.Update(GetMousePosition());
        Fishron.Update(headFish.getPosition());
        LeFishe.Update(Fishron.getPosition());
        Terry.Update(LeFishe.getPosition());

        BeginDrawing();
        
        ClearBackground(SKYBLUE);
            // Water
            DrawRectangle(0, waterLevelStartY, GetScreenWidth(), GetScreenHeight() - waterLevelStartY, BLUE);

            headFish.Draw();
            Fishron.Draw();
            LeFishe.Draw();
            Terry.Draw();

            DrawTexture(cursorTexture, GetMouseX(), GetMouseY(), WHITE);
        EndDrawing();

    }

    UnloadTexture(tardigradeTexture);
    UnloadTexture(cursorTexture);
    CloseWindow();

    return 0;
}