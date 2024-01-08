#include "raylib.h"
#include "raymath.h"
#include <cmath>

class Fish {

private:
    Texture2D texture;

    float speed = 10;
    float turnSpeed = 50;
    float rotation = 0;

    Vector2 direction;
    Vector2 desiredPosition;
    Vector2 position;

public:

    Fish(Texture2D texture, Vector2 position, Vector2 desiredPosition);
    Vector2 turnTo(Vector2 current, Vector2 desired, float turn);
    void Update();
    void Draw();
};

Fish::Fish(Texture2D texture, Vector2 position, Vector2 desiredPosition) {
    Fish::texture = texture;
    Fish::position = position;
    Fish::desiredPosition = desiredPosition;

    Fish::direction.x = 1;
    Fish::direction.y = 0;
}

Vector2 Fish::turnTo(Vector2 current, Vector2 desired, float turn) {
    current = Vector2Normalize(current);
    desired = Vector2Normalize(desired);

    if (current.y > desired.y) {
        current.y = cos(turn * current.y) + sin(turn * current.x);
        current.x = cos(turn * current.x) - sin(turn * current.y);
    }
    else {
        //current.y = cos(-turn * current.y) + sin(-turn * current.x);
        //current.x = cos(-turn * current.x) - sin(-turn * current.y);
    }

    return current;
}

void Fish::Update() {

    Fish::direction = Fish::turnTo(Fish::direction, Fish::desiredPosition, Fish::turnSpeed);
    Fish::rotation = atan2(direction.x, direction.y);

    


}

void Fish::Draw() {
    DrawTextureEx(Fish::texture, Fish::position, Fish::rotation, 1, WHITE);
}