#pragma once
#include <SFML/Graphics.hpp>
#include "ClassBar.h"
#include "ClassBall.h"
#include "ClassField.h"

class Bonus //abstract class realizing bonus work
{
private:
    float radius;
    float x, y;

public:
    Bonus(float posX, float posY); //default constructor
    ~Bonus(void) {} //default destructor

    virtual void Trigger(std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) = 0; /*
    purely virtual method of triggering a bonus on the field*/

    bool Move(float userWindowHeight, std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field); /*
    bonus movement in the field*/
    void DrawBonus(std::shared_ptr <sf::RenderWindow> window); //bonus drawing in the field
};

class ChangeBar:public Bonus //class of a bonus of changing bar's sizes
{
public:
    ChangeBar(float posX, float posY) :Bonus(posX, posY) {} //constructor
    ~ChangeBar(void) {} //destructor

    void Trigger(std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) override; //resizes bar
};

class ChangeBall :public Bonus //class  of a bonus of changing ball's speed
{
public:
    ChangeBall(float posX, float posY) :Bonus(posX, posY) {} //constructor
    ~ChangeBall(void) {} //destructor

    void Trigger(std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) override; /*
    changes the speed of the ball*/
};

class BallStick :public Bonus //class  of a bonus for ball's sticking
{
public:
    BallStick(float posX, float posY) :Bonus(posX, posY) {}  //constructor
    ~BallStick(void) {} //destructor

    void Trigger(std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) override; /*
    ball sticking to the bar*/
};

class BallBottom :public Bonus //class of a bonus, which sets a bottom for the ball
{
public:
    BallBottom(float posX, float posY) :Bonus(posX, posY) {} //constructor
    ~BallBottom(void) {} //destructor

    void Trigger(std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) override; /*
    a bottom appears for a ball that works like a bar*/
};

class RandomPath :public Bonus //class of a bonus, which sets a random path for the ball
{
public:
    RandomPath(float posX, float posY) :Bonus(posX, posY) {} //constructor
    ~RandomPath(void) {} //destructor

    void Trigger(std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) override; /*
    change at any moment of the ball trajectory*/
};

class MovingBrickBonus :public Bonus //class of a bonus, which adds a moving brick to field
{
public:
    MovingBrickBonus(float posX, float posY) :Bonus(posX, posY) {} //constructor
    ~MovingBrickBonus(void) {} //destructor

    void Trigger(std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) override; /*
    the appearance of a moving block on the field*/
};