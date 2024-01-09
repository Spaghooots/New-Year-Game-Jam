#include <raylib.h>

class Food
{
public:
    Food();
    ~Food();
    void Update(float frameTime, float waterLevelY);
    void Draw();
private:
    Texture2D _texture;
    Vector2 _position;
    float _gravityInAir;
    float _gravityInWater;
};


Food::Food()
{
    _position = Vector2{GetRandomValue(0, GetScreenWidth() * 100) / 100.0f, 0};
    _gravityInAir = 300.0f;
    _gravityInWater = 125.0f;
}

Food::~Food() {}

void Food::Update(float frameTime, float waterLevelY)
{
    _position = Vector2Add(_position, Vector2{0, ((_position.y <= waterLevelY) ? _gravityInAir : _gravityInWater) * frameTime});

    if (_position.y > GetScreenHeight() / 2)
    {
        Food::~Food();
    }
}

void Food::Draw()
{
    DrawCircle(_position.x, _position.y, 16, WHITE);
}