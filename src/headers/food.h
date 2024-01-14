#include <iostream>
#include <raylib.h>
#include <string>

class Food
{
public:
    Food(Texture2D texture);
    ~Food();
    void Update();
    void Draw();
    float getX() { return _xPos; }
    float getY() { return _yPos; }
    float getRadius() { return _texture.width / 2.0f; }
private:
    Texture2D _texture;
    float _xPos;
    float _yPos;
    float _gravityInAir = 300.0f;
    float _gravityInWater = 125.0f;
    int _foodSpeedUpY = 50;
};


Food::Food(Texture2D texture)
{ 
    _texture = texture;
    _xPos = GetRandomValue(0, ((GetScreenWidth()-_texture.width) * 100)) / 100.0f;
    _yPos = -texture.height / 2.0f;
}

Food::~Food() {}

void Food::Update()
{
    _yPos += (_yPos <= _foodSpeedUpY ? _gravityInAir : _gravityInWater) * GetFrameTime();
}

void Food::Draw()
{
    DrawTexture(_texture, _xPos, _yPos, WHITE);
}