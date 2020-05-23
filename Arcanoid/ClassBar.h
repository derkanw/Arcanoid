#pragma once
#include <SFML/Graphics.hpp>

class Bar
{
private:
    float height, width;
    float defaultWidth;
    float x;
    float defaultX, y;
    unsigned ballStick;

public:
    Bar(float barHeight, float barWidth, float posX, float posY);
    ~Bar(void) {}

    float GetHeight(void);
    float GetWidth(void);
    float GetDefaultWidth(void);
    float GetPosX(void);
    float GetPosY(void);
    unsigned GetBallStick(void);

    void SetWidth(float newWidth);
    void SetBallStick(unsigned newBallStick);

    void Move(float userWindowWidth);
    void BallOut(void);

    void DrawBar(std::shared_ptr <sf::RenderWindow> window);
};