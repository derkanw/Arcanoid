#include <vector>
#include "ClassBall.h"

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
    speedX = newSpeedX;
    speedY = newSpeedY;
}

void Ball::CollisionWithWindow(float userWindowWidth, float offsetHeight)
{
    if ((x <= 0) || (x >= userWindowWidth - 2 * radius))
        speedX *= -1;
    if (y <= offsetHeight)
        speedY *= -1;
}

void Ball::BallOut(float userWindowHeight, std::shared_ptr <Bar> bar)
{
    if (y >= userWindowHeight)
    {
        speedX = 0;
        speedY = 0;
        x = defaultX;
        y = defaultY;
        bar->BallOut();
    }
}

bool Ball::CollisionWithShape(float shapeHeight, float shapeWidth, float shapeX, float shapeY)
{
    bool result = false;
    float leftBoarder = shapeX - 2 * radius;
    float rightBoarder = shapeX + shapeWidth;
    float upperBoarder = shapeY - 2 * radius;
    float lowerBoarder = shapeY + shapeHeight;

    if ((x >= leftBoarder) && (x <= rightBoarder) && ((abs(y - upperBoarder) < abs(speedY/2)) || (abs(y - lowerBoarder) <abs(speedY/2))))
    {
        speedY *= -1;
        result = true;
    }
    if ((y >= lowerBoarder) && (y <= upperBoarder) && ((abs(x - leftBoarder)< abs(speedX/2)) || (abs(x - rightBoarder) < abs(speedX/2))))
    {
        speedX *= -1;
        result = true;
    }
    return result;
}

bool Ball::Move(float userWindowHeight, float userWindowWidth, float offsetHeight, std::shared_ptr <Bar> bar, std::shared_ptr <Field> field)
{
    std::vector <Brick> bricksMatrix = field->GetBricksMatrix();

    x += speedX;
    y += speedY;

    if ((speedX == 0) && (speedY == 0))
    {
        x = bar->GetPosX() + bar->GetWidth() / 2 - radius;
        y = bar->GetPosY() - 2 * radius;
    }

    BallOut(userWindowHeight, bar);
    CollisionWithWindow(userWindowWidth, offsetHeight);
    CollisionWithShape(bar->GetHeight(), bar->GetWidth(), bar->GetPosX(), bar->GetPosY());

    for (unsigned k = 0; k < bricksMatrix.size(); k++)
        if (CollisionWithShape(bricksMatrix[k].GetHeight(), bricksMatrix[k].GetWidth(), bricksMatrix[k].GetPosX(), bricksMatrix[k].GetPosY()))
        {
            field->DeleteBrick(k);
            break;
        }

    return true;
}

void Ball::DrawBall(std::shared_ptr <sf::RenderWindow> window)
{
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::White);
    circle.setPosition(x, y);

    window->draw(circle);
}