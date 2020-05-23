#include <vector>
#include <cmath>
#include "ClassBall.h"
#define DEFAULT_SPEED 10

Ball::Ball(float ballRadius, float posX, float posY)
{
    radius = ballRadius;
    x = posX;
    y = posY;
    defaultX = posX;
    defaultY = posY;
    speedX = 0;
    speedY = 0;
    ballBottom = false;
}

void Ball::SetSpeed(float newSpeedX, float newSpeedY)
{
    speedX *= newSpeedX;
    speedY *= newSpeedY;
}

void Ball::SetBallBottom(bool value)
{
    ballBottom = value;
}

void Ball::StartMove(float userWindowWidth) //переделать нормально
{
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
    {
        float default_speed = userWindowWidth;
        speedX = DEFAULT_SPEED*(defaultX - x) / default_speed;
        speedY = -sqrt(DEFAULT_SPEED* DEFAULT_SPEED - speedX * speedX);
    }
}

void Ball::CollisionWithWindow(float userWindowWidth, float offsetHeight)
{
    if ((x < abs(speedX)) || (x > userWindowWidth - 2 * radius - speedX))
        speedX *= -1;
    if (y < offsetHeight - abs(speedY))
        speedY *= -1;
}

int Ball::BallOut(float userWindowHeight, std::shared_ptr <Bar> bar)
{
    if (y+2*radius>= userWindowHeight)
    {
        if (!ballBottom)
        {
            speedX = 0;
            speedY = 0;
            x = defaultX;
            y = defaultY;
            bar->BallOut();
            return -3;
        }
        else
        {
            speedY *= -1;
            ballBottom = false;
        }
    }
    return 0;
}

unsigned Ball::CollisionWithShape(float shapeHeight, float shapeWidth, float shapeX, float shapeY, unsigned ballStick) //пределать попадание в углы
{
    unsigned result = 0;
    float leftBoarder = shapeX - 2 * radius;
    float rightBoarder = shapeX + shapeWidth;
    float upperBoarder = shapeY - 2 * radius;
    float lowerBoarder = shapeY + shapeHeight;

    float speed = sqrt(speedX * speedX + speedY * speedY);

    if (((upperBoarder - y >= 0) && (upperBoarder - y < speed) && (leftBoarder - x >= 0) && (leftBoarder - x < speed)) ||
        ((upperBoarder - y >= 0) && (upperBoarder - y < speed) && (x - rightBoarder >= 0) && (x - rightBoarder < abs(speed))) ||
        ((y - lowerBoarder >= 0) && (y - lowerBoarder < abs(speed)) && (leftBoarder - x >= 0) && (leftBoarder - x < speed)) ||
        ((y - lowerBoarder >= 0) && (y - lowerBoarder < abs(speed)) && (x - rightBoarder >= 0) && (x - rightBoarder < abs(speed))))
    {
        if (ballStick > 0)
        {
            speedX = 0;
            speedY = 0;
            subX = x;
            result=2;
        }
        else
        {
            speedX *= -1;
            speedY *= -1;
            result = 1;
        }
    }

    if ((x > leftBoarder) && (x < rightBoarder) && (((upperBoarder - y >=0)&&(upperBoarder - y < speedY)) || ((y - lowerBoarder >= 0) && (y - lowerBoarder < abs(speedY)))))
    {
        if (ballStick > 0)
        {
            speedX = 0;
            speedY = 0;
            subX = x;
            result =2;
        }
        else
        {
            speedY *= -1;
            result = 1;
        }
    }
    if ((y < lowerBoarder) && (y > upperBoarder) && (((leftBoarder - x >= 0) && (leftBoarder - x < speedX)) || ((x - rightBoarder >= 0) && (x - rightBoarder < abs(speedX)))))
    {
        if (ballStick > 0)
        {
            speedX = 0;
            speedY = 0;
            subX = x;
            result= 2;
        }
        else
        {
            speedX *= -1;
            result = 1;
        }
    }
    return result;
}

void Ball::Move(std::shared_ptr <Bar> bar, float userWindowWidth)
{
    x += speedX;
    y += speedY;

    if ((speedX == 0) && (speedY == 0))
    {
        if (bar->GetBallStick() > 0)
            x = bar->GetPosX() + abs(subX- bar->GetPosX());
        else x = bar->GetPosX() + bar->GetWidth() / 2 - radius;
        y = bar->GetPosY() - 2 * radius;
        StartMove(userWindowWidth);
    }
}

void Ball::DrawBall(std::shared_ptr <sf::RenderWindow> window)
{
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::White);
    circle.setPosition(x, y);

    window->draw(circle);
}