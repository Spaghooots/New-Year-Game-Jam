/* 
All my fishies :) (Do not delete this comment!)
    Fish headFish = Fish(chaserFishTexture, Vector2{screenWidth/2, screenHeight/2});
    Fish Fishron = Fish(chaserFishTexture, Vector2{screenWidth/2, screenHeight/2});
    Fish LeFishe = Fish(chaserFishTexture, Vector2{screenWidth/2, screenHeight/2});
    Fish Terry = Fish(chaserFishTexture, Vector2{screenWidth/2, screenHeight/2});
*/



#include <raylib.h>
#include <raymath.h>

class Fish {

private:

    // Fish Variables
    Texture2D texture;

    float speed = 5;
    float turnDampen = 20;
    float rotation = 0;

    Vector2 direction;
    Vector2 position;
    Vector2 origin;

    Rectangle rectSlice;
    Rectangle rectDraw;

public:

    // Fish Functions
    Fish(Texture2D texture, Vector2 position, float turnDampen);
    Vector2 getPosition() { return position; }
    Vector2 getPositionFollow() { return Vector2Subtract(position,Vector2Scale(Vector2Normalize(direction), texture.width/2 + 10)); }
    Texture2D getTexture() { return texture; }
    void Update(Vector2 desiredPosition);
    void Draw();
};

Fish::Fish(Texture2D texture, Vector2 position, float turnDampen) {

    // Start facing to the right
    Fish::direction.x = 1;
    Fish::direction.y = 0;

    // Find origin
    Fish::origin.x = texture.width/2;
    Fish::origin.y = texture.height/2;

    // Set Constructor variables
    Fish::turnDampen = turnDampen;
    Fish::texture = texture;
    Fish::position = position;

    // Create slice of spritesheet (whole thing in this case)
    Fish::rectSlice = Rectangle{0, 0, (float)texture.width, (float)texture.height};
}


void Fish::Update(Vector2 desiredPosition) {

    // Rotate fish to desired position
    float angle = Vector2Angle(Fish::direction, Vector2Negate(Vector2Subtract(Fish::position, desiredPosition)));
    Fish::direction = Vector2Rotate(Fish::direction, angle/turnDampen);

    // Get angle for drawing
    Fish::rotation = Vector2Angle(Fish::direction, Vector2{1,0});

    // Move forward
    Fish::position = Vector2Add(Fish::position, Vector2Scale(Vector2Normalize(Fish::direction), speed));

    // Update Draw rectangle
    Fish::rectDraw = Rectangle{position.x, position.y, (float)texture.width * 2, (float)texture.height};

    // Flip fish
    if (Fish::direction.x < 0) {
        Fish::rectSlice.height = -Fish::texture.height;
    } else {
        Fish::rectSlice.height = Fish::texture.height;
    }


}

void Fish::Draw() {
    
    DrawTexturePro(Fish::texture, Fish::rectSlice, Fish::rectDraw, Fish::origin, Fish::rotation * -(180 / PI), WHITE);
}