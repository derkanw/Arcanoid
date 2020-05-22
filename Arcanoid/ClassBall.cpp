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
}

void Ball::SetSpeed(float newSpeedX, float newSpeedY)
{
    speedX *= newSpeedX;
    speedY *= newSpeedY;
}

void Ball::StartMove(std::shared_ptr <Field> field) //переделать нормально
{
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
    {
        float default_speed = field->GetWidth();
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
    if (y >= userWindowHeight)
    {
        speedX = 0;
        speedY = 0;
        x = defaultX;
        y = defaultY;
        bar->BallOut();
        return -3;
    }
    return 0;
}

bool Ball::CollisionWithShape(float shapeHeight, float shapeWidth, float shapeX, float shapeY) //пределать попадание в углы
{
    bool result = false;
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
        speedX *= -1;
        speedY *= -1;
        result = true;
    }

    if ((x > leftBoarder) && (x < rightBoarder) && (((upperBoarder - y >=0)&&(upperBoarder - y < speedY)) || ((y - lowerBoarder >= 0) && (y - lowerBoarder < abs(speedY)))))
    {
        speedY *= -1;
        result = true;
    }
    if ((y < lowerBoarder) && (y > upperBoarder) && (((leftBoarder - x >= 0) && (leftBoarder - x < speedX)) || ((x - rightBoarder >= 0) && (x - rightBoarder < abs(speedX)))))
    {
        speedX *= -1;
        result = true;
    }
    return result;
}

void Ball::Move(std::shared_ptr <Bar> bar, std::shared_ptr <Field> field)
{
    x += speedX;
    y += speedY;

    if ((speedX == 0) && (speedY == 0))
    {
        x = bar->GetPosX() + bar->GetWidth() / 2 - radius;
        y = bar->GetPosY() - 2 * radius;
        StartMove(field);
    }
}

void Ball::DrawBall(std::shared_ptr <sf::RenderWindow> window)
{
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::White);
    circle.setPosition(x, y);

    window->draw(circle);
}