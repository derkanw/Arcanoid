#include "Bonus.h"
#define CHANGE_NUM (float)1.5
#define BONUS_SPEED 1
#define STICK_NUM 3

Bonus::Bonus(float posX, float posY) //default constructor
{
    radius = 5;
    x = posX;
    y = posY;
}

bool Bonus::Move(float userWindowHeight, std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field)/*
bonus movement in the field*/
{
    float leftBoarder = bar->GetPosX() - 2 * radius;
    float rightBoarder = bar->GetPosX() + bar->GetWidth();
    float upperBoarder = bar->GetPosY() - 2 * radius;
    float lowerBoarder = bar->GetPosY() + bar->GetHeight();
    float bonusOut = userWindowHeight - BONUS_SPEED;

    y += BONUS_SPEED;

    if ((x >= leftBoarder) && (x <= rightBoarder) && (y >= upperBoarder) && (y <= lowerBoarder))
    {
        Trigger(bar, ball, field);
        return true;
    }
    else if (y >= bonusOut)
        return true;
    return false;
}

void Bonus::DrawBonus(std::shared_ptr <sf::RenderWindow> window) //bonus drawing in the field
{
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::Yellow);
    circle.setPosition(x, y);

    window->draw(circle);
}

void ChangeBar::Trigger(std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) //resizes bar
{
    switch (rand() % 2)
    {
    case 0:
        if (bar->GetWidth()> bar->GetDefaultWidth() / CHANGE_NUM)
            bar->SetWidth(bar->GetDefaultWidth() / CHANGE_NUM);
        break;
    case 1:
        if (bar->GetWidth()< bar->GetDefaultWidth() * CHANGE_NUM)
            bar->SetWidth(bar->GetDefaultWidth() * CHANGE_NUM);
        break;
    }
}

void ChangeBall::Trigger(std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) /*
changes the speed of the ball*/
{
    switch (rand() % 2)
    {
    case 0:
            ball->SetSpeed(1 / CHANGE_NUM, 1/ CHANGE_NUM);
        break;
    case 1:
            ball->SetSpeed(CHANGE_NUM, CHANGE_NUM);
        break;
    }
}

void BallStick::Trigger(std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) /*
ball sticking to the bar*/
{
    bar->SetBallStick(STICK_NUM);
}

void BallBottom::Trigger(std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) /*
a bottom appears for a ball that works like a bar*/
{
    ball->SetBallBottom(true);
}

void RandomPath::Trigger(std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) /*
change at any moment of the ball trajectory*/
{
    ball->SetRandomPath(true);
}

void MovingBrickBonus::Trigger(std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) /*
the appearance of a moving block on the field*/
{
    field->SetMovingBrick();
}