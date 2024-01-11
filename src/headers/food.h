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
    float getX() { return _xPos; }
    float getY() { return _yPos; }
    float getRadius() { return _radius; }
private:
    float _xPos = GetRandomValue(0, GetScreenWidth() * 100) / 100.0f;
    float _yPos = -_radius;
    float _gravityInAir = 300.0f;
    float _gravityInWater = 125.0f;
    float _radius = 6;
};


Food::Food() {}

Food::~Food() {}

void Food::Update(float waterLevelY)
{
    _yPos += (_yPos <= waterLevelY ? _gravityInAir : _gravityInWater) * GetFrameTime();
}

void Food::Draw()
{
    DrawCircle((int)_xPos, (int)_yPos, _radius, YELLOW);
}