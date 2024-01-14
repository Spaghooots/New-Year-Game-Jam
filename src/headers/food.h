#include <iostream>
#include <raylib.h>
#include <string>

class Food
{
public:
    Food(Texture2D texture);
    ~Food();
    void Update(float waterLevelY);
    void Draw();
    float getX() { return _xPos; }
    float getY() { return _yPos; }
    float getRadius() { return _texture.width / 2.0f; }
private:
    Texture2D _texture;
    float _xPos = GetRandomValue(0, GetScreenWidth() * 100) / 100.0f;
    float _yPos;
    float _gravityInAir = 300.0f;
    float _gravityInWater = 125.0f;
};


Food::Food(Texture2D texture)
{ 
    _texture = texture;
    _yPos = -texture.height / 2.0f;
}

Food::~Food() {}

void Food::Update(float waterLevelY)
{
    _yPos += (_yPos <= waterLevelY ? _gravityInAir : _gravityInWater) * GetFrameTime();
}

void Food::Draw()
{
    DrawTexture(_texture, _xPos, _yPos, WHITE);
}