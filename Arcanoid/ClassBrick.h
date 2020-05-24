#pragma once
#include <SFML/Graphics.hpp>

class Brick
{
protected:
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
    sf::Color GetColor(void);

    virtual void SetSpeedX(float newSpeedX) {}
    void SetHealth(int addition);
    virtual float GetSpeedX(void) { return 0; }

    virtual void Move(float userWindowWidth) {}

    void DrawBrick(std::shared_ptr <sf::RenderWindow> window);
};

class MovingBrick :public Brick
{
private:
    float speedX;

public:
    MovingBrick(float brickHeight, float brickWidth, float posX, float posY);
    ~MovingBrick(void) {}

    float GetSpeedX(void) override;
    void SetSpeedX(float newSpeedX) override;
    void Move(float userWindowWidth) override;
};