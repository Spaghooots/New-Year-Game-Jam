#include <iostream>
#include <vector>
#include <raylib.h>
#include "fish.h"
#include "food.h"


int main(void) {

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Template");

    Texture2D chaserFishTexture = LoadTexture("assets/graphics/chaserFish.png");
    Texture2D cursorTexture = LoadTexture("assets/graphics/fish_food_cursor.png");

    
    /* All my fishies (Do not delete this comment!)
    Fish headFish = Fish(chaserFishTexture, Vector2{screenWidth/2, screenHeight/2});
    Fish Fishron = Fish(chaserFishTexture, Vector2{screenWidth/2, screenHeight/2});
    Fish LeFishe = Fish(chaserFishTexture, Vector2{screenWidth/2, screenHeight/2});
    Fish Terry = Fish(chaserFishTexture, Vector2{screenWidth/2, screenHeight/2});
    */
    
    
    std::vector<Food> foodItems;
    std::vector<Fish> fishies;

    int fishAmount = 2;

    fishies.push_back(Fish(chaserFishTexture, Vector2{screenWidth/2, screenHeight/2}));
    fishies.push_back(Fish(chaserFishTexture, Vector2{0, 0}));

    int foodTimer = 0;
    int foodSpawnDelayMilliseconds = 300000;
    int waterLevelY = 50;

    SetTargetFPS(60);
    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_SPACE)) {
            fishies.push_back(Fish(chaserFishTexture, Vector2{screenWidth/2, screenHeight/2}));
            fishAmount ++;
        }
        
        fishies[0].Update(GetMousePosition());
        for (int i = 1; i < fishAmount; i++) {
            fishies[i].Update(fishies[i-1].getPosition());
        }

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

            DrawText("Press space to spawn a fish", 100, 100, 20, WHITE);

            for (Fish fishie : fishies) {
                fishie.Draw();
            }

            for (Food foodItem : foodItems)
            {
                foodItem.Draw();
            }

            DrawTexture(cursorTexture, GetMouseX(), GetMouseY(), WHITE);
        EndDrawing();

    }

    UnloadTexture(chaserFishTexture);
    UnloadTexture(cursorTexture);
    CloseWindow();

    return 0;
}