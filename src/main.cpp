#include <string>
#include <vector>
#include <raylib.h>
#include <algorithm>
#include "fish.h"
#include "food.h"


int main(void) {

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Food Chain");
    InitAudioDevice();

    // Load Textures
    SetTextureFilter(GetFontDefault().texture, TEXTURE_FILTER_POINT);
    Texture2D backgroundTexture = LoadTexture("assets/graphics/background.png");
    Texture2D chaserFishTexture = LoadTexture("assets/graphics/chaser_fish.png");
    Texture2D playerFishTexture = LoadTexture("assets/graphics/player_fish.png");
    Texture2D foodTexture = LoadTexture("assets/graphics/fish_treat.png");

    // Load Sounds
    Sound eatSound = LoadSound("assets/sounds/eat.wav");
    Sound wrongSound = LoadSound("assets/sounds/wrong.wav");
    Sound deathSound = LoadSound("assets/sounds/death.wav");

    // Load misc.
    Music music = LoadMusicStream("assets/sounds/fishSong.wav");
    Font fontLemon = LoadFont("assets/graphics/lemon_regular.ttf");

    PlayMusicStream(music);
    
    // World Variables
    std::vector<Food> foodItems;
    std::vector<Fish> fishies;
    enum GameState { Menu, Gameplay, GameOver};
    GameState gameState = Menu;
    float musicVol = .2;

    // Fish Variables
    int score = 0;

    // Food Variables
    float foodTimer = 0;
    float foodSpawnDelaySeconds = 3.0f;

    // Player Variables
    float playerHitRad = 10;


    // Game Loop
    SetTargetFPS(60);
    while (!WindowShouldClose()) {

        SetMusicVolume(music, musicVol);
        UpdateMusicStream(music);

        switch(gameState)
        {
            case Menu: {
                if (IsKeyPressed(KEY_SPACE)) {
                    fishies.push_back(Fish(chaserFishTexture));
                    gameState = Gameplay;
                    DisableCursor();
                }
                break;
            }
            case Gameplay: {

                musicVol = .8;
<<<<<<< Updated upstream
                // Window Bounds (x)
                if (GetMouseX() < 0) SetMousePosition(0, GetMouseY());
                else if (GetMouseX() > screenWidth) SetMousePosition(screenWidth, GetMouseY());

                // Window Bounds (y)
                if (GetMouseY() < 0) SetMousePosition(GetMouseX(), 0);
                else if (GetMouseY() > screenHeight) SetMousePosition(GetMouseX(), screenHeight);

                // Fish Update
                fishies[0].Update(GetMousePosition());
                for (int i = 1; i < fishies.size(); i++) {
                    fishies[i].Update(fishies[i-1].getPositionFollow());
                }

                // Fish Collision
                for (Fish fishie : fishies) {
                    if (CheckCollisionCircles(GetMousePosition(), playerHitRad, fishie.getPosition(), fishie.getTexture().height/2)) {
                        gameState = GameOver;
                        PlaySound(deathSound);
                        EnableCursor();
                    }
                }
=======

                // Window Bounds (Could be cleaned up better)=
                if (GetMouseX() > 0 && GetMouseX() < screenWidth &&
                    GetMouseY() > 0 && GetMouseY() < screenHeight)
                {
                    playerFishPosition = GetMousePosition();
                    playerFishDelta = GetMouseDelta();
                }
                else
                {
                    if (GetMouseX() < 0) playerFishPosition.x = 0;
                    if (GetMouseX() > GetScreenWidth()) playerFishPosition.x = GetScreenWidth();
                    if (GetMouseY() < 0) playerFishPosition.y = 0;
                    if (GetMouseY() > GetScreenHeight()) playerFishPosition.y = GetScreenHeight();
                }

                
>>>>>>> Stashed changes
                
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
                        fishies.push_back(Fish(chaserFishTexture));

                        // Delete food
                        foodItems.erase(foodItems.begin() + i);
                        PlaySound(eatSound);

                        // Increment score
                        score++;
                    }
                }

                // Food Update
                for (int i = 0; i < foodItems.size(); i++)
                {
                    foodItems[i].Update();

                    if (foodItems[i].getY() >= GetScreenHeight())
                    {
                        if (score > 0) score--;
                        foodItems.erase(foodItems.begin() + i);
                        PlaySound(wrongSound);
                    }
                }

                // Fish Update
                fishies[0].Update(playerFishPosition);
                for (int i = 1; i < fishies.size(); i++) {
                    fishies[i].Update(fishies[i-1].getPositionFollow());
                }

                // Fish Collision
                for (Fish fishie : fishies) {
                    if (CheckCollisionCircles(playerFishPosition, playerHitRad, fishie.getPosition(), fishie.getTexture().height/2)) {
                        gameState = GameOver;
                        PlaySound(deathSound);
                        EnableCursor();
                    }
                }

                break;
            }
            case GameOver: {
                // Reset Variables
                
                musicVol = .2;
                if (IsKeyPressed(KEY_SPACE)) {
                    DisableCursor();
                    fishies = std::vector<Fish>{};
                    fishies.push_back(Fish(chaserFishTexture));
                    foodItems = std::vector<Food>{};
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

            // Draw Fish
            for (Fish fishie : fishies) {
                fishie.Draw();
            }

            // Draw Food
            for (Food foodItem : foodItems)
            {
                foodItem.Draw();
            }

            // Drawing here depends on state
            switch (gameState)
            {
                case Menu: {
                    // Title
                    DrawTextPro(fontLemon, "Food Chain", Vector2{GetScreenWidth() / 2.0f, GetScreenHeight() * 0.3f}, 
                        Vector2{MeasureText("Food Chain", 48) / 2.0f, 0.5f}, 0, 48, 0.3f, SKYBLUE);

                    DrawTextPro(fontLemon, "Press 'space' to play!", Vector2{GetScreenWidth() / 2.0f + 15, GetScreenHeight() * 0.5f}, 
                        Vector2{MeasureText("Press 'space' to play!", 32) / 2.0f, 0.5f}, 0, 32, 0.3f, BLACK);
                    break;
                }
                case Gameplay: {
                    // Determining direction player fish faces
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

                    // Score text
                    DrawTextEx(fontLemon, ("Score: " + std::to_string(score)).c_str(), Vector2{0, 0}, 32, 0.3f, WHITE);
                    break;
                }
                case GameOver: {
                    // Game Over!
                    DrawTextPro(fontLemon, "Game Over!", Vector2{GetScreenWidth() / 2.0f, GetScreenHeight() * 0.3f}, 
                        Vector2{MeasureText("Game Over!", 48) / 2.0f, 0.5f}, 0, 48, 0.3f, ORANGE);
                    
                    // Final Score
                    DrawTextPro(fontLemon, ("Final score: " + std::to_string(score)).c_str(), Vector2{GetScreenWidth() / 2.0f, GetScreenHeight() * 0.4f}, 
                        Vector2{MeasureText(("Final score: " + std::to_string(score)).c_str(), 24) / 2.0f, 0.5f}, 0, 24, 0.3f, WHITE);

                    // Prompt
                    DrawTextPro(fontLemon, "Press 'space' to try again.", Vector2{GetScreenWidth() / 2.0f + 30, GetScreenHeight() * 0.5f}, 
                        Vector2{MeasureText("Press 'space' to try again.", 30) / 2.0f, 0.5f}, 0, 30, 0.3f, BLACK);
                    break;
                }
            }

        EndDrawing();
    }

    UnloadMusicStream(music);

    UnloadSound(eatSound);
    UnloadSound(wrongSound);

    UnloadTexture(backgroundTexture);
    UnloadTexture(chaserFishTexture);
    UnloadTexture(playerFishTexture);
    UnloadTexture(foodTexture);
    CloseWindow();


    return 0;
}
