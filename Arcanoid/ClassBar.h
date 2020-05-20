#pragma once
#include <SFML/Graphics.hpp>

class Bar
{
private:
    float height, width;
    float defaultWidth;
    float x;
    float defaultX, y;

public:
    Bar(float barHeight, float barWidth, float posX, float posY);
    ~Bar(void) {}

    float GetHeight(void);
    float GetWidth(void);
    float GetPosX(void);
    float GetPosY(void);

    void Move(float userWindowWidth);
    void BallOut(void);

    void DrawBar(std::shared_ptr <sf::RenderWindow> window);
};