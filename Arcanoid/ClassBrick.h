#pragma once
#include <SFML/Graphics.hpp>

class Brick
{
private:
    float height, width;
    float x, y;
    int health;
    sf::Color color;

public:
    Brick(float brickHeight, float brickWidth, float posX, float posY, int brickHealth, sf::Color brickColor);
    ~Brick(void) {}

    float GetHeight(void);
    float GetWidth(void);
    float GetPosX(void);
    float GetPosY(void);
    int GetHealth(void);
    void SetHealth(int addition);

    void DrawBrick(std::shared_ptr <sf::RenderWindow> window);
};