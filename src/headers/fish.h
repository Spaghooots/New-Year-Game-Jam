#include "raylib.h"
#include "raymath.h"

class Fish {

private:
    Texture2D texture;

    float speed;
    float turnDampen = 10;
    float rotation = 0;

    Vector2 direction;
    Vector2 desiredPosition;
    Vector2 position;
    Vector2 origin;

    Rectangle rectSlice;
    Rectangle rectDraw;

public:

    Fish(Texture2D texture, Vector2 position, float speed);
    Vector2 getPosition() { return Vector2Subtract(position,Vector2Scale(Vector2Normalize(direction), texture.width/2 + 10)); }
    void Update(Vector2 desiredPosition);
    void Draw();
};

Fish::Fish(Texture2D texture, Vector2 position, float speed) {

    Fish::direction.x = 1;
    Fish::direction.y = 1;

    Fish::origin.x = texture.width/2;
    Fish::origin.y = texture.height/2;


    Fish::texture = texture;
    Fish::position = position;
    Fish::speed = speed;
    //Fish::desiredPosition = desiredPosition;

    Fish::rectSlice = Rectangle{0, 0, (float)texture.width, (float)texture.height};
}


void Fish::Update(Vector2 desiredPosition) {

    Fish::direction = Vector2Subtract(desiredPosition, Fish::position);
    Fish::rotation = Vector2Angle(Fish::direction, Vector2{1,0});


    Fish::position = Vector2Add(Fish::position, Vector2Scale(Fish::direction, speed/100));
    Fish::rectDraw = Rectangle{position.x, position.y, (float)texture.width, (float)texture.height};


}

void Fish::Draw() {

    DrawTexturePro(Fish::texture, Fish::rectSlice, Fish::rectDraw, Fish::origin, Fish::rotation * -(180 / PI), WHITE);
}