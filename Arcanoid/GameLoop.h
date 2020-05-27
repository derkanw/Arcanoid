#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "ClassField.h"
#include "ClassBar.h"
#include "ClassBall.h"
#include "Bonus.h"

class GameLoop //class of the gameplay
{
private:
    float userWindowWidth, userWindowHeight;
    int score;

    float fieldWindowHeight, fieldWindowWidth;
    float offsetHeight;
    unsigned numberBricksInRow, numberBricksInColumn;

    float ballRadius;
    float ballX, ballY;

    float barHeight, barWidth;
    float barX, barY = ballY;

    std::shared_ptr <sf::RenderWindow> window;
    std::shared_ptr <Field> field;
    std::shared_ptr <Bar> bar;
    std::shared_ptr <Ball> ball;
    std::vector <std::shared_ptr<Bonus>> bonusesMatrix;

public:
    GameLoop(void); //constructor
    ~GameLoop(void) {} //destructor

    void Start(void); //main cycle of the gameplay
    void AllMovement(void); //implements all the movement in the gameplay
    void AllColisions(void); //checks all collisions in the gameplay
    void AllDrawing(void); //draws all the elements of the gameplay

    void CollisionWithBricks(void); /*implements a check for the stocking of the ball with bricks
    and the loss of the bonus when removing the bricks*/

    void ChooseBonus(float bonusX, float bonusY); //choosing type of bonus for working
    void StickingWork(void); //implements the work of sticking the ball to the bar
    void BonusesWork(void); //bonus life cycle with drawing, movement and hitting the bar

    void CreateText(void); //displays the score

    void End(void); //if the game is over
};