#include <memory>
#include "ClassBar.h"
#define SPEED_BAR 1

Bar::Bar(float barHeight, float barWidth, float posX, float posY)
{
    height = barHeight;
    width = barWidth;
    defaultWidth = barWidth;
    x = posX;
    defaultX = posX;
    y = posY;
    ballStick = 0;
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

float Bar::GetDefaultWidth(void)
{
    return defaultWidth;
}

unsigned Bar::GetBallStick(void)
{
    return ballStick;
}

void Bar::SetWidth(float newWidth)
{
    width = newWidth;
}

void Bar::SetBallStick(unsigned newBallStick)
{
    ballStick += newBallStick;
}

void Bar::BallOut(void)
{
    width = defaultWidth;
    x = defaultX;
    ballStick = 0;
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