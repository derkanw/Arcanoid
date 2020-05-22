#pragma once
#include <SFML/Graphics.hpp>
#include "ClassBar.h"
#include "ClassField.h"
#include "ClassBrick.h"

class Ball
{
private:
    float radius;
    float x, y;
    float defaultX, defaultY;
    float speedX, speedY;

public:
    Ball(float ballRadius, float posX, float posY);
    ~Ball(void) {}

    void SetSpeed(float newSpeedX, float newSpeedY);

    int BallOut(float userWindowHeight, std::shared_ptr <Bar> bar);
    void CollisionWithWindow(float userWindowWidth, float offsetHeight);
    bool CollisionWithShape(float shapeHeight, float shapeWidth, float shapeX, float shapeY);
    void StartMove(std::shared_ptr <Field> field);
    void Move(std::shared_ptr <Bar> bar, std::shared_ptr <Field> field);
    
    void DrawBall(std::shared_ptr <sf::RenderWindow> window);
};