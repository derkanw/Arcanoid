#pragma once
#include <SFML/Graphics.hpp>
#include "ClassBar.h"
#include "ClassBrick.h"

class Ball
{
private:
    float radius;
    float x, y;
    float defaultX, defaultY;
    float speedX, speedY;
    float barOffset;

    bool ballBottom;
    bool randomPath;

public:
    Ball(float ballRadius, float posX, float posY);
    ~Ball(void) {}

    float GetPosX(void);

    void SetSpeed(float newSpeedX, float newSpeedY);
    void SetBallBottom(bool value);
    void SetBarOffset(float newOffset);
    void SetRandomPath(float newRandomPath);

    int BallOut(float userWindowHeight, std::shared_ptr <Bar> bar);
    void CollisionWithWindow(float userWindowWidth, float offsetHeight);
    unsigned CollisionWithShape(float shapeHeight, float shapeWidth, float shapeX, float shapeY, unsigned ballStick = 0);
    void StartMove(float userWindowWidth);
    void Move(std::shared_ptr <Bar> bar, float userWindowWidth);
    
    void DrawBall(std::shared_ptr <sf::RenderWindow> window);
};