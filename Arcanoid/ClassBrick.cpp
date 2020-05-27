#include "ClassBrick.h"
#define BRICK_SPEED (float)0.5

Brick::Brick(float brickHeight, float brickWidth, float posX, float posY, int brickHealth, sf::Color brickColor) //constructor
{
    height = brickHeight;
    width = brickWidth;
    x = posX;
    y = posY;
    health = brickHealth;
    color = brickColor;
}

float Brick::GetHeight(void) //returns brick's height
{
    return height;
}

float Brick::GetWidth(void) //returns brick's width
{
    return width;
}

float Brick::GetPosX(void) //returns the position of the brick in x-coordinate
{
    return x;
}

float Brick::GetPosY(void) //returns the position of the brick in y-coordinate
{
    return y;
}

int Brick::GetHealth(void) //returns brick's points of health
{
    return health;
}

sf::Color Brick::GetColor(void) //returns brick's color
{
    return color;
}

void Brick::SetHealth(int addition) //gives new value to health bricks
{
    health += addition;
}

void Brick::DrawBrick(std::shared_ptr <sf::RenderWindow> window) //drawing a brick on the field
{
    sf::RectangleShape shape(sf::Vector2f(width, height));

    shape.setFillColor(color);
    shape.setPosition(x, y);
    shape.setOutlineThickness((height + width) / -40);
    shape.setOutlineColor(sf::Color::Black);

    window->draw(shape);
}

MovingBrick::MovingBrick(float brickHeight, float brickWidth, float posX, float posY) :
    Brick(brickHeight, brickWidth, posX, posY, 3, sf::Color::Magenta) //constructor
{
    speedX = BRICK_SPEED * (float)pow(-1, rand() % 2);
}

float MovingBrick::GetSpeedX(void) //returns brick's speed
{
    return speedX;
}

void MovingBrick::SetSpeedX(float newSpeedX) //changes the direction of the speed of brick
{
    speedX *= newSpeedX;
}

void MovingBrick::Move(float userWindowWidth) //brick's movement across the field
{
    if (x <= 0 || x + width >= userWindowWidth)
        speedX *= -1;
    x += speedX;
}