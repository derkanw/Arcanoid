#pragma once
#include <SFML/Graphics.hpp>
#include "ClassBar.h"
#include "ClassBrick.h"

class Ball //class realizing the action of the ball on the playing field
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
    Ball(float ballRadius, float posX, float posY); //constructor
    ~Ball(void) {} //destructor

    float GetPosX(void); //returns the position of the ball in the x-coordinate

    void SetSpeed(float newSpeedX, float newSpeedY); //changes the speed of the ball in both coordinates
    void SetBallBottom(bool value); //sets the appearance of the bottom working as a bar
    void SetBarOffset(float newOffset); //sets the position of the ball relative to the coordinates of the bar
    void SetRandomPath(float newRandomPath); //the possibility of the ball randomly changing its trajectory

    int BallOut(float userWindowHeight, std::shared_ptr <Bar> bar); //if the bar did not catch the ball
    unsigned BallIsSticking(void); //if sticking the ball to the bar works
    void CollisionWithWindow(float userWindowWidth, float offsetHeight); //collision with the borders of the playing field
    unsigned CollisionWithShape(float shapeHeight, float shapeWidth, float shapeX, float shapeY, unsigned ballStick = 0); /*
    method for checking the collision of a ball with a rectangle (bar or brick)
    that returns 0 - no collision, 1 - normal collision, 2 - sticking collision*/

    void BallMoveRandom(void); //if the bonus of a happy change in the trajectory of the ball worked
    void ZeroSpeed(std::shared_ptr <Bar> bar, float userWindowWidth); //if the ball is in place of its appearance
    void StartMove(float userWindowWidth); //sets the start of ball movement by pressing a key
    void Move(std::shared_ptr <Bar> bar, float userWindowWidth); //ball movement on the playing field
    
    void DrawBall(std::shared_ptr <sf::RenderWindow> window); //drawing ball gameplay
};