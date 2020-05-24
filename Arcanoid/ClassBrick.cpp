#include "ClassBrick.h"
#define BRICK_SPEED 0.5

Brick::Brick(float brickHeight, float brickWidth, float posX, float posY, int brickHealth, sf::Color brickColor)
{
    height = brickHeight;
    width = brickWidth;
    x = posX;
    y = posY;
    health = brickHealth;
    color = brickColor;
}

float Brick::GetHeight(void)
{
    return height;
}

float Brick::GetWidth(void)
{
    return width;
}

float Brick::GetPosX(void)
{
    return x;
}

float Brick::GetPosY(void)
{
    return y;
}

int Brick::GetHealth(void)
{
    return health;
}

sf::Color Brick::GetColor(void)
{
    return color;
}

void Brick::SetHealth(int addition)
{
    health += addition;
}

void Brick::DrawBrick(std::shared_ptr <sf::RenderWindow> window)
{
    sf::RectangleShape shape(sf::Vector2f(width, height));

    shape.setFillColor(color);
    shape.setPosition(x, y);
    shape.setOutlineThickness((height + width) / -40);
    shape.setOutlineColor(sf::Color::Black);

    window->draw(shape);
}

MovingBrick::MovingBrick(float brickHeight, float brickWidth, float posX, float posY) :Brick(brickHeight, brickWidth, posX, posY, 3, sf::Color::Magenta)
{
    speedX = BRICK_SPEED * (float)pow(-1, rand() % 2);
}

void MovingBrick::Move(float userWindowWidth)
{
    if (x <= 0 || x + width >= userWindowWidth)
        speedX *= -1;
    x += speedX;
}

float MovingBrick::GetSpeedX(void)
{
    return speedX;
}

void MovingBrick::SetSpeedX(float newSpeedX)
{
    speedX *= newSpeedX;
}