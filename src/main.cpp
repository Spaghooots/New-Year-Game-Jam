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
    Texture2D chaserFishTexture = LoadTexture("assets/graphics/chaser_fish.png");
    Texture2D playerFishTexture = LoadTexture("assets/graphics/player_fish.png");
    Texture2D foodTexture = LoadTexture("assets/graphics/fish_treat.png");
    
    // World Vectors
    std::vector<Food> foodItems;
    std::vector<Fish> fishies;
    enum GameState { Menu, Gameplay, GameOver};
    GameState gameState = Gameplay;

    // Fish Variables
    int score = 0;
    fishies.push_back(Fish(chaserFishTexture, Vector2{screenWidth/2, screenHeight/2}, 20));

    // Food Variables
    float foodTimer = 0;
    float foodSpawnDelaySeconds = 3.0f;
    std::string treatsHudMessage = "Fish Treats Eaten: ";
    int waterLevelY = 50;

    // Player Variables
    float playerHitRad = 10;


    // Game Loop
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        switch(gameState)
        {
            case Menu: {
                break;
            }
            case Gameplay: {
                // Fish Update
                fishies[0].Update(GetMousePosition());
                for (int i = 1; i < fishies.size(); i++) {
                    fishies[i].Update(fishies[i-1].getPositionFollow());
                }

                // Fish Collision
                for (Fish fishie : fishies) {
                    if (CheckCollisionCircles(GetMousePosition(), playerHitRad, fishie.getPosition(), fishie.getTexture().height/2)) {
                        gameState = GameOver;
                    }
                }
                
                // Spawn Food
                foodTimer += GetFrameTime();
                if (foodTimer >= foodSpawnDelaySeconds)
                {
                    foodItems.push_back(Food(foodTexture));
                    foodTimer = 0;
                }

                // Food Collision
                for (int i = 0; i < foodItems.size(); i++) {
                    Vector2 foodCenterPoint = Vector2{foodItems[i].getX() + foodItems[i].getRadius(), foodItems[i].getY() + foodItems[i].getRadius()};
                    if (CheckCollisionCircles(GetMousePosition(), playerHitRad, foodCenterPoint, foodItems[i].getRadius())) {
                        
                        // Spawn Fish
                        if(GetMouseX() < screenWidth/2) {
                            fishies.push_back(Fish(chaserFishTexture, Vector2{screenWidth+20, (float)GetRandomValue(0, screenHeight)}, 10));
                        } else {
                            fishies.push_back(Fish(chaserFishTexture, Vector2{-20, (float)GetRandomValue(0, screenHeight)}, 10));
                        }

                        // Delete food
                        foodItems.erase(foodItems.begin() + i);

                        // Increment score
                        score++;
                    }
                }

                // Food Update
                for (int i = 0; i < foodItems.size(); i++)
                {
                    foodItems[i].Update(waterLevelY);

                    if (foodItems[i].getY() >= GetScreenHeight())
                    {
                        foodItems.erase(foodItems.begin() + i);
                    }
                }

                break;
            }
            case GameOver: {
                // Reset Variables
                if (IsKeyPressed(KEY_SPACE)) {
                    fishies = std::vector<Fish>{};
                    foodItems = std::vector<Food>{};
                    fishies.push_back(Fish(chaserFishTexture, Vector2{screenWidth/2, screenHeight/2}, 20));
                    score = 0;
                    gameState = Gameplay;
                }
                break;
            }
        }

        BeginDrawing();
            // Water Texture
            ClearBackground(SKYBLUE);
            DrawTexture(backgroundTexture, 0, 0, WHITE);

            // Drawing here depends on state
            switch (gameState)
            {
                case Menu: {
                    break;
                }
                case Gameplay: {
                    // Determining direction fish faces
                    Rectangle sourceRect;
                    if (GetMouseDelta().x > 0) {
                        sourceRect = Rectangle{0, 0, float(playerFishTexture.width), float(playerFishTexture.height)};
                    } else if (GetMouseDelta().x < 0) {
                        sourceRect = Rectangle{0, 0, -float(playerFishTexture.width), float(playerFishTexture.height)};
                    }

                    // Fish center point
                    Vector2 center = Vector2{float(playerFishTexture.width) / 2.0f, float(playerFishTexture.height / 2.0f)};

                    // Fish drawing
                    DrawTexturePro(playerFishTexture, sourceRect, Rectangle{GetMousePosition().x, GetMousePosition().y, 
                        float(playerFishTexture.width), float(playerFishTexture.height)}, center, 0, WHITE);

                    DrawText((treatsHudMessage + std::to_string(score)).c_str(), 5, 5, 24, GOLD);            
                    break;
                }
                case GameOver: {
                    DrawText("press space to reset", 100, 100, 20, WHITE);
                    break;
                }
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
