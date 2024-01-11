#include <iostream>
#include <raylib.h>
#include <string>

class Food
{
public:
    Food();
    ~Food();
    void Update(float waterLevelY);
    void Draw();
    float GetY() { return yPos; }
private:
    float xPos = GetRandomValue(0, GetScreenWidth() * 100) / 100.0f;
    float yPos = 0.0f;
    float _gravityInAir = 300.0f;
    float _gravityInWater = 125.0f;
    float _radius = 6;
};


Food::Food() {}

Food::~Food() {}

void Food::Update(float waterLevelY)
{
    yPos += (yPos <= waterLevelY ? _gravityInAir : _gravityInWater) * GetFrameTime();
    if (yPos > GetScreenHeight() + _radius / 2.0f)
    {
        Food::~Food();
    }
}

void Food::Draw()
{
    DrawCircle((int)xPos, (int)yPos, _radius, YELLOW);
}