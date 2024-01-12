#include <string>
#include <vector>
#include <raylib.h>
#include "fish.h"
#include "food.h"


int main(void) {

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Template");

    // Load Textures
    Texture2D backgroundTexture = LoadTexture("assets/graphics/background.png");
    Texture2D chaserFishTexture = LoadTexture("assets/graphics/chaserFish.png");
    Texture2D playerFishTexture = LoadTexture("assets/graphics/playerFish.png");
    Texture2D foodTexture = LoadTexture("assets/graphics/fish_treat.png");
    
    // World Vectors
    std::vector<Food> foodItems;
    std::vector<Fish> fishies;

    // Fish Variables
    int fishAmount = 1;
    fishies.push_back(Fish(chaserFishTexture, Vector2{screenWidth/2, screenHeight/2}, 20));

    // Food Variables
    float foodTimer = 0;
    float foodSpawnDelaySeconds = 3.0f;
    int waterLevelY = 50;

    // Player Variables
    bool isAlive = true;
    float playerHitRad = 10;


    // Game Loop
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        // Check Collisions Fish
        for (Fish fishie : fishies) {
            if (CheckCollisionCircles(GetMousePosition(), playerHitRad, fishie.getPosition(), fishie.getTexture().height/2)) {
                isAlive = false;
            }
        }

        // Check Collision Food
        for (int i = 0; i < foodItems.size(); i++) {
            Vector2 foodCenterPoint = Vector2{foodItems[i].getX() + foodItems[i].getRadius(), foodItems[i].getY() + foodItems[i].getRadius()};
            if (CheckCollisionCircles(GetMousePosition(), playerHitRad, foodCenterPoint, foodItems[i].getRadius())) {
                
                // Spawn Fish
                if(GetMouseX() < screenWidth/2) {
                    fishies.push_back(Fish(chaserFishTexture, Vector2{screenWidth+20, (float)GetRandomValue(0, screenHeight)}, 10));
                } else {
                    fishies.push_back(Fish(chaserFishTexture, Vector2{-20, (float)GetRandomValue(0, screenHeight)}, 10));
                }
                fishAmount ++;

                // Delete food
                foodItems.erase(foodItems.begin() + i);
            }
        }
        
        // Check if alive
        if (isAlive) {

            // Fish Movement
            fishies[0].Update(GetMousePosition());
            for (int i = 1; i < fishAmount; i++) {
                fishies[i].Update(fishies[i-1].getPositionFollow());
            }

            // Spawn Food
            foodTimer += GetFrameTime();
            if (foodTimer >= foodSpawnDelaySeconds)
            {
                foodItems.push_back(Food(foodTexture));
                foodTimer = 0;
            }
        }
        // Let player reset if dead
        else if (IsKeyPressed(KEY_SPACE)) {
            fishies = std::vector<Fish>{};
            foodItems = std::vector<Food>{};
            fishies.push_back(Fish(chaserFishTexture, Vector2{screenWidth/2, screenHeight/2}, 20));
            fishAmount = 1;

            isAlive = true;
        }

        
        // Delete food that falls
        for (int i = 0; i < foodItems.size(); i++)
        {
            foodItems[i].Update(waterLevelY);

            if (foodItems[i].getY() >= GetScreenHeight())
            {
                foodItems.erase(foodItems.begin() + i);
            }
        }

        BeginDrawing();
            ClearBackground(SKYBLUE);
            // Water
            DrawRectangle(0, waterLevelY, GetScreenWidth(), GetScreenHeight() - waterLevelY, BLUE);
            DrawTexture(backgroundTexture, 0, 0, WHITE);
            
            if (isAlive) {
                Rectangle sourceRect;
                if (GetMouseDelta().x > 0) {
                    sourceRect = Rectangle{0, 0, float(playerFishTexture.width), float(playerFishTexture.height)};
                } else if (GetMouseDelta().x < 0) {
                    sourceRect = Rectangle{0, 0, -float(playerFishTexture.width), float(playerFishTexture.height)};
                }

                Vector2 center = Vector2{float(playerFishTexture.width) / 2.0f, float(playerFishTexture.height / 2.0f)};

                DrawTexturePro(playerFishTexture, sourceRect, Rectangle{GetMousePosition().x, GetMousePosition().y, 
                    float(playerFishTexture.width), float(playerFishTexture.height)}, center, 0, WHITE);
            }
            else {
                // Draw death message when dead
                DrawText("press space to reset", 100, 100, 20, WHITE);
            }

            // Draw Fish
            for (Fish fishie : fishies) {
                fishie.Draw();
            }

            // Draw Food
            for (Food foodItem : foodItems)
            {
                foodItem.Draw();
            }

            
        EndDrawing();
    }

    UnloadTexture(backgroundTexture);
    UnloadTexture(chaserFishTexture);
    UnloadTexture(playerFishTexture);
    UnloadTexture(foodTexture);
    CloseWindow();

    return 0;
}
