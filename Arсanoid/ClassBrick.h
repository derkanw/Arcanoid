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

    void DrawBrick(std::shared_ptr <sf::RenderWindow> window);
};