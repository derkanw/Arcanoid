#pragma once
#include <SFML/Graphics.hpp>

class Brick //class of individual bricks making up the playing field
{
protected:
    float height, width;
    float x, y;
    int health;
    sf::Color color;

public:
    Brick(float brickHeight, float brickWidth, float posX, float posY, int brickHealth, sf::Color brickColor); //default constructor
    ~Brick(void) {} //default destructor

    float GetHeight(void); //returns brick's height
    float GetWidth(void); //returns brick's width
    float GetPosX(void); //returns the position of the brick in x-coordinate
    float GetPosY(void); //returns the position of the brick in y-coordinate
    int GetHealth(void); //returns brick's points of health
    sf::Color GetColor(void); //returns brick's color

    void SetHealth(int addition); //gives new value to health bricks

    virtual float GetSpeedX(void) { return 0; } /*virtual method of rotation of the speed of the bricks
    to implement the movement of the bricks in the child class*/
    virtual void SetSpeedX(float newSpeedX) {} /*virtual method of assigning the speed of a brick
    to implement the movement of a bricks in a child class*/
    virtual void Move(float userWindowWidth) {} //virtual method for implementing a move of a brick in a child class

    void DrawBrick(std::shared_ptr <sf::RenderWindow> window); //drawing a brick on the field
};

class MovingBrick :public Brick //a child class of a bonus implementing the action of a bonus - a moving brick
{
private:
    float speedX;

public:
    MovingBrick(float brickHeight, float brickWidth, float posX, float posY); //constructor
    ~MovingBrick(void) {} //destructor

    float GetSpeedX(void) override; //returns brick's speed
    void SetSpeedX(float newSpeedX) override;  //changes the direction of the speed of brick
    void Move(float userWindowWidth) override; //brick's movement across the field
};