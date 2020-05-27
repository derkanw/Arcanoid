#pragma once
#include <SFML/Graphics.hpp>

class Bar //bar control class
{
private:
    float height, width;
    float defaultWidth;
    float x, y;
    float defaultX;
    unsigned ballStick;

public:
    Bar(float barHeight, float barWidth, float posX, float posY); //constructor
    ~Bar(void) {} //destructor

    float GetHeight(void); //returns current bar's height
    float GetWidth(void); //returns current bar's width
    float GetDefaultWidth(void); //returns default bar's width
    float GetPosX(void); //returns current bar's position of x-coordinate
    float GetPosY(void); //returns current bar's position of y-coordinate
    unsigned GetBallStick(void); //returns number of ball's sticking

    void SetWidth(float newWidth); //assigns a new bar's width
    void SetBallStick(unsigned newBallStick); //assigns a new number of ball's sticking

    void Move(float userWindowWidth); //bar's movement using the keyboard
    void BallOut(void); //if the ball goes out of bounds

    void DrawBar(std::shared_ptr <sf::RenderWindow> window); //drawing bar's gameplay
};