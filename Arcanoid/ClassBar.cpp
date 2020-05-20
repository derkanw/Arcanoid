#include <memory>
#include "ClassBar.h"
#define SPEED_BAR 10

Bar::Bar(float barHeight, float barWidth, float posX, float posY)
{
    height = barHeight;
    width = barWidth;
    defaultWidth = barWidth;
    x = posX;
    defaultX = posX;
    y = posY;
}

float Bar::GetHeight(void)
{
    return height;
}

float Bar::GetWidth(void)
{
    return width;
}

float Bar::GetPosX(void)
{
    return x;
}

float Bar::GetPosY(void)
{
    return y;
}

void Bar::BallOut(void)
{
    x = defaultX;
}

void Bar::Move(float userWindowWidth)
{
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
        if (x >= 0)
            x -= SPEED_BAR;
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
        if (x <= userWindowWidth - width)
            x += SPEED_BAR;
}

void Bar::DrawBar(std::shared_ptr <sf::RenderWindow> window)
{
    sf::RectangleShape shape(sf::Vector2f(width, height));

    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(x, y);

    window->draw(shape);
}