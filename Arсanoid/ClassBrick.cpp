#include "ClassBrick.h"

Brick::Brick(float brickHeight, float brickWidth, float posX, float posY, int brickHealth, sf::Color brickColor)
{
    height = brickHeight;
    width = brickWidth;
    x = posX;
    y = posY;
    health = brickHealth;
    color = brickColor;
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