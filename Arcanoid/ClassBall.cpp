#include <vector>
#include <cmath>
#include "ClassBall.h"
#define DEFAULT_SPEED 3
#define CHANCE_OF_RANDOM 15
#define POINTS_OF_OUT -3

Ball::Ball(float ballRadius, float posX, float posY) //constructor
{
    radius = ballRadius;
    x = posX;
    y = posY;
    defaultX = posX;
    defaultY = posY;
    speedX = 0;
    speedY = 0;

    barOffset = 0;
    ballBottom = false;
    randomPath = false;
}

float Ball::GetPosX(void) //returns the position of the ball in the x-coordinate
{
    return x;
}

void Ball::SetSpeed(float newSpeedX, float newSpeedY) //changes the speed of the ball in both coordinates
{
    speedX *= newSpeedX;
    speedY *= newSpeedY;
}

void Ball::SetBallBottom(bool value) //sets the appearance of the bottom working as a bar
{
    ballBottom = value;
}

void Ball::SetBarOffset(float newOffset) //sets the position of the ball relative to the coordinates of the bar
{
    barOffset = newOffset;
}

void Ball::SetRandomPath(float newRandomPath) //the possibility of the ball randomly changing its trajectory
{
    randomPath = newRandomPath;
}

void Ball::StartMove(float userWindowWidth) //sets the start of ball movement by pressing a key
{
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
    {
        speedX = DEFAULT_SPEED * (defaultX - x) / userWindowWidth;
        speedY = -sqrt(DEFAULT_SPEED * DEFAULT_SPEED - speedX * speedX);
    }
}

void Ball::CollisionWithWindow(float userWindowWidth, float offsetHeight) //collision with the borders of the playing field
{
    float leftBoarder = abs(speedX);
    float rightBoarder = userWindowWidth - 2 * radius - speedX;
    float upperBoarder = offsetHeight - abs(speedY);

    if ((x < leftBoarder) || (x > rightBoarder))
        speedX *= -1;
    if (y < upperBoarder)
        speedY *= -1;
}

int Ball::BallOut(float userWindowHeight, std::shared_ptr <Bar> bar) //if the bar did not catch the ball
{
    float lowerBoarder = userWindowHeight - 2 * radius;

    if (y >= lowerBoarder)
    {
        if (!ballBottom)
        {
            speedX = 0;
            speedY = 0;
            x = defaultX;
            y = defaultY;
            randomPath = 0;

            bar->BallOut();
            return POINTS_OF_OUT;
        }
        else
        {
            speedY *= -1;
            ballBottom = false;
        }
    }
    return 0;
}

unsigned Ball::BallIsSticking(void) //if sticking the ball to the bar works
{
    speedX = 0;
    speedY = 0;
    return 2;
}

unsigned Ball::CollisionWithShape(float shapeHeight, float shapeWidth, float shapeX, float shapeY, unsigned ballStick) /*
method for checking the collision of a ball with a rectangle (bar or brick)
that returns 0 - no collision, 1 - normal collision, 2 - sticking collision*/
{
    unsigned result = 0;

    float leftBoarder = shapeX - 2 * radius;
    float rightBoarder = shapeX + shapeWidth;
    float upperBoarder = shapeY - 2 * radius;
    float lowerBoarder = shapeY + shapeHeight;

    float speed = sqrt(speedX * speedX + speedY * speedY);

    bool withUpperBoarder = (upperBoarder - y >= 0) && (upperBoarder - y < speedY);
    bool withLowerBoarder = (y - lowerBoarder >= 0) && (y - lowerBoarder < abs(speedY));
    bool withLeftBoarder = (leftBoarder - x >= 0) && (leftBoarder - x < speedX);
    bool withRightBoarder = (x - rightBoarder >= 0) && (x - rightBoarder < abs(speedX));

    bool upperSide = (upperBoarder - y >= 0) && (upperBoarder - y < speed);
    bool lowerSide = (y - lowerBoarder >= 0) && (y - lowerBoarder < speed);
    bool leftSide = (leftBoarder - x >= 0) && (leftBoarder - x < speed);
    bool rightSide = (x - rightBoarder >= 0) && (x - rightBoarder < speed);

    if ((x > leftBoarder) && (x < rightBoarder) && (withUpperBoarder || withLowerBoarder)) //vertical collision
    {
        if (ballStick > 0)
            result = BallIsSticking();
        else
        {
            speedY *= -1;
            result = 1;
        }
    }

    if ((y < lowerBoarder) && (y > upperBoarder) && (withLeftBoarder || withRightBoarder)) //horizontal collision
    {
        if (ballStick > 0)
            result = BallIsSticking();
        else
        {
            speedX *= -1;
            result = 1;
        }
    }

    if ((leftSide || rightSide) && (upperSide || lowerSide)) //collision with corners
    {
        if (ballStick > 0)
            result = BallIsSticking();
        else
        {
            speedX *= -1;
            speedY *= -1;
            result = 1;
        }
    }
    return result;
}

void Ball::BallMoveRandom(void) //if the bonus of a happy change in the trajectory of the ball worked
{
    if (randomPath && (rand() % 100 < CHANCE_OF_RANDOM))
    {
        speedX *= (float)pow(-1, rand() % 2);
        speedY *= (float)pow(-1, rand() % 2);
        randomPath = false;
    }
}

void Ball::ZeroSpeed(std::shared_ptr <Bar> bar, float userWindowWidth) //if the ball is in place of its appearance
{
    if ((speedX == 0) && (speedY == 0))
    {
        if (bar->GetBallStick() > 0)
            x = bar->GetPosX() + barOffset;
        else
            x = bar->GetPosX() + bar->GetWidth() / 2 - radius;

        y = bar->GetPosY() - 2 * radius;
        StartMove(userWindowWidth);
    }
}

void Ball::Move(std::shared_ptr <Bar> bar, float userWindowWidth) //ball movement on the playing field
{
    BallMoveRandom();
    x += speedX;
    y += speedY;
    ZeroSpeed(bar, userWindowWidth);
}

void Ball::DrawBall(std::shared_ptr <sf::RenderWindow> window) //drawing ball gameplay
{
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::White);
    circle.setPosition(x, y);

    window->draw(circle);
}