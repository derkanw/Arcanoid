#include <memory>
#include "ClassBar.h"
#define SPEED_BAR 1

Bar::Bar(float barHeight, float barWidth, float posX, float posY) //constructor
{
    height = barHeight;
    width = barWidth;
    defaultWidth = barWidth;
    x = posX;
    y = posY;
    defaultX = posX;
    ballStick = 0;
}

float Bar::GetHeight(void)  //returns current bar's height
{
    return height;
}

float Bar::GetWidth(void) //returns current bar's width
{
    return width;
}

float Bar::GetDefaultWidth(void)  //returns default bar's width
{
    return defaultWidth;
}

float Bar::GetPosX(void) //returns current bar's position of x-coordinate
{
    return x;
}

float Bar::GetPosY(void) //returns current bar's position of y-coordinate
{
    return y;
}

unsigned Bar::GetBallStick(void) //returns number of ball's sticking
{
    return ballStick;
}

void Bar::SetWidth(float newWidth) //assigns a new bar's width
{
    width = newWidth;
}

void Bar::SetBallStick(unsigned newBallStick) //assigns a new number of ball's sticking
{
    ballStick += newBallStick;
}

void Bar::BallOut(void) //if the ball goes out of bounds
{
    width = defaultWidth;
    x = defaultX;
    ballStick = 0;
}

void Bar::Move(float userWindowWidth) //bar's movement using the keyboard
{
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
        if (x >= 0)
            x -= SPEED_BAR;
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
        if (x <= userWindowWidth - width)
            x += SPEED_BAR;
}

void Bar::DrawBar(std::shared_ptr <sf::RenderWindow> window) //drawing bar's gameplay
{
    sf::RectangleShape shape(sf::Vector2f(width, height));

    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(x, y);

    window->draw(shape);
}