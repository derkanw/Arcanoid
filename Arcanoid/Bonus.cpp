#include "Bonus.h"
#define CHANGE_NUM float(1.5)

Bonus::Bonus(float posX, float posY, sf::Color bonusColor, unsigned bonysType)
{
    radius = 5;
    x = posX;
    y = posY;
    type = bonysType;
    color = bonusColor;
}

bool Bonus::Move(float userWindowHeight, std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball)
{
    bool result = false;
    y += 10;
    if ((x + 2 * radius >= bar->GetPosX()) && (x <= bar->GetPosX() + bar->GetWidth()) && (y + 2 * radius >= bar->GetPosY()) && (y <= bar->GetPosY() + bar->GetHeight()))
    {
        Trigger(bar, ball);
        result = true;
    }
    else if (y + 10 >= userWindowHeight)
        result = true;
    return result;
}

void Bonus::DrawBonus(std::shared_ptr <sf::RenderWindow> window)
{
    sf::CircleShape circle(radius);
    circle.setFillColor(color);
    circle.setPosition(x, y);

    window->draw(circle);
}

void ChangeBar::Trigger(std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball)
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

void ChangeBall::Trigger(std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball)
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