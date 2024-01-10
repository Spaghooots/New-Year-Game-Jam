#include <iostream>
#include <raylib.h>
#include <string>

class Food
{
public:
    Food();
    ~Food();
    void Update(float frameTime, float waterLevelY);
    void Draw();
private:
    float xPos = GetRandomValue(0, GetScreenWidth() * 100) / 100.0f;
    float yPos = 0.0f;
    float _gravityInAir = 300.0f;
    float _gravityInWater = 125.0f;
};


Food::Food() {}

Food::~Food() {}

void Food::Update(float frameTime, float waterLevelY)
{
    yPos += (yPos <= waterLevelY ? _gravityInAir : _gravityInWater) * frameTime;
    if (yPos > GetScreenHeight() / 2)
    {
        Food::~Food();
    }
}

void Food::Draw()
{
    DrawCircle((int)xPos, (int)yPos, 16, YELLOW);
}