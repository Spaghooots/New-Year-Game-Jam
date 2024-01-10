#include <iostream>
#include <vector>
#include <raylib.h>
#include "fish.h"
#include "food.h"


int main(void) {

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Template");

    Texture2D tardigradeTexture = LoadTexture("assets/graphics/tardigrade.png");
    Texture2D cursorTexture = LoadTexture("assets/graphics/fish_food_cursor.png");
    
    // All my fishies :)
    Fish headFish = Fish(tardigradeTexture, Vector2{screenWidth/2, screenHeight/2});
    Fish Fishron = Fish(tardigradeTexture, Vector2{screenWidth/2, screenHeight/2});
    Fish LeFishe = Fish(tardigradeTexture, Vector2{screenWidth/2, screenHeight/2});
    Fish Terry = Fish(tardigradeTexture, Vector2{screenWidth/2, screenHeight/2});

    std::vector<Food> foodItems;

    int foodTimer = 0;
    int foodSpawnDelayMilliseconds = 300000;
    int waterLevelY = 50;

    SetTargetFPS(60);
    while (!WindowShouldClose()) {

        SetWindowSize(fmin(GetScreenWidth(), screenWidth), fmin(GetScreenHeight(), screenHeight));
        
        headFish.Update(GetMousePosition());
        Fishron.Update(headFish.getPosition());
        LeFishe.Update(Fishron.getPosition());
        Terry.Update(LeFishe.getPosition());

        foodTimer += GetFrameTime();
        if (foodTimer + GetFrameTime() >= foodSpawnDelayMilliseconds)
        {
            foodItems.push_back(Food());
            foodTimer = 0;
        }

        for (Food foodItem : foodItems)
        {
            foodItem.Update(GetFrameTime(), waterLevelY);
        }

        BeginDrawing();
            ClearBackground(SKYBLUE);
            // Water
            DrawRectangle(0, waterLevelY, GetScreenWidth(), GetScreenHeight() - waterLevelY, BLUE);

            headFish.Draw();
            Fishron.Draw();
            LeFishe.Draw();
            Terry.Draw();

            for (Food foodItem : foodItems)
            {
                foodItem.Draw();
            }

            DrawTexture(cursorTexture, GetMouseX(), GetMouseY(), WHITE);
        EndDrawing();

    }

    UnloadTexture(tardigradeTexture);
    UnloadTexture(cursorTexture);
    CloseWindow();

    return 0;
}