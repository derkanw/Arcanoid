#pragma once
#include <SFML/Graphics.hpp>
#include "ClassBar.h"
#include "ClassBall.h"
#include "ClassField.h"

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

    virtual void Trigger(std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) = 0;

    bool Move(float userWindowHeight, std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field);

    void DrawBonus(std::shared_ptr <sf::RenderWindow> window);
};

class ChangeBar:public Bonus
{
public:
    ChangeBar(float posX, float posY) :Bonus(posX, posY, sf::Color::Yellow, 0) {}
    ~ChangeBar(void) {}

    void Trigger(std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) override;
};

class ChangeBall :public Bonus
{
public:
    ChangeBall(float posX, float posY) :Bonus(posX, posY, sf::Color::Yellow, 1) {}
    ~ChangeBall(void) {}

    void Trigger(std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) override;
};

class BallStick :public Bonus
{
public:
    BallStick(float posX, float posY) :Bonus(posX, posY, sf::Color::Yellow, 2) {}
    ~BallStick(void) {}

    void Trigger(std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) override;
};

class BallBottom :public Bonus
{
public:
   BallBottom(float posX, float posY) :Bonus(posX, posY, sf::Color::Yellow, 3) {}
   ~BallBottom(void) {}

    void Trigger(std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) override;
};

class RandomPath :public Bonus
{
public:
    RandomPath(float posX, float posY) :Bonus(posX, posY, sf::Color::Yellow, 4) {}
    ~RandomPath(void) {}

    void Trigger(std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) override;
};

class MovingBrickBonus :public Bonus
{
public:
    MovingBrickBonus(float posX, float posY) :Bonus(posX, posY, sf::Color::Yellow, 5) {}
    ~MovingBrickBonus(void) {}

    void Trigger(std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) override;
};