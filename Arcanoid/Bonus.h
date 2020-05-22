#pragma once
#include <SFML/Graphics.hpp>
#include "ClassBar.h"
#include "ClassBall.h"

class Bonus
{
private:
    float radius;
    float x, y;
    unsigned type;
    sf::Color color;

public:
    Bonus(float posX, float posY, sf::Color bonusColor, unsigned bonysType);
    ~Bonus(void) {}

    virtual void Trigger(std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball) = 0;

    bool Move(float userWindowHeight, std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball);

    void DrawBonus(std::shared_ptr <sf::RenderWindow> window);
};

class ChangeBar:public Bonus
{
public:
    ChangeBar(float posX, float posY) :Bonus(posX, posY, sf::Color::Yellow, 0) {}
    ~ChangeBar(void) {}

    void Trigger(std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball) override;
};

class ChangeBall :public Bonus
{
public:
    ChangeBall(float posX, float posY) :Bonus(posX, posY, sf::Color::Magenta, 1) {}
    ~ChangeBall(void) {}

    void Trigger(std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball) override;
};