#include "raylib.h"
#include "raymath.h"

class Fish {

private:
    Texture2D texture;

    float speed = 10;
    float turnSpeed = 50;
    float rotation = 0;

    Vector2 direction;
    Vector2 desiredPosition;
    Vector2 position;
    Vector2 origin;

    Rectangle rectSlice;
    Rectangle rectDraw;

public:

    Fish(Texture2D texture, Vector2 position);
    Vector2 turnTo(Vector2 current, Vector2 desired, float turn);
    void Update(Vector2 desiredPosition);
    void Draw();
};

Fish::Fish(Texture2D texture, Vector2 position) {

    Fish::direction.x = 1;
    Fish::direction.y = 1;

    Fish::origin.x = texture.width/2;
    Fish::origin.y = texture.height/2;


    Fish::texture = texture;
    Fish::position = position;
    //Fish::desiredPosition = desiredPosition;

    Fish::rectSlice = Rectangle{0, 0, (float)texture.width, (float)texture.height};
    Fish::rectDraw = Rectangle{position.x, position.y, (float)texture.width, (float)texture.height};
}


// This is not used right now, I need to start over with it
Vector2 Fish::turnTo(Vector2 current, Vector2 desired, float turn) {
    current = Vector2Normalize(current);
    desired = Vector2Normalize(desired);

    if (current.y > desired.y) {
        current.y = cos(turn * current.y) + sin(turn * current.x);
        current.x = cos(turn * current.x) - sin(turn * current.y);
    }
    else if (current.y > desired.y) {
        current.y = cos(-turn * current.y) + sin(-turn * current.x);
        current.x = cos(-turn * current.x) - sin(-turn * current.y);
    }

    return current;
}

void Fish::Update(Vector2 desiredPosition) {

    // I am trying to make the fish look at the mouse pointer
    Fish::rotation = Vector2Angle(Vector2Subtract(desiredPosition, Fish::position), Vector2{1,0});

    


}

void Fish::Draw() {
    DrawTexturePro(Fish::texture, Fish::rectSlice, Fish::rectDraw, Fish::origin, Fish::rotation, WHITE);
}