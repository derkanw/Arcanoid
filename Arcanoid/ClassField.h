#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <memory>
#include "ClassBrick.h"

class Field //class that implements storage and actions on a set of bricks in the playing field
{
private:
    float height, width;
    float offset;
    unsigned bricksInRow, bricksInColumn;
    unsigned numberMovingBricks;

    unsigned score;

    std::vector <std::shared_ptr<Brick>> bricksMatrix;

    std::array <sf::Color, 3> colorsMatrix = { sf::Color::Green, sf::Color::Red, sf::Color::Cyan };

public:
    Field(float fieldWindowHeight, float fieldWindowWidth, unsigned numberBricksInRow,
        unsigned numberBricksInColumn, float offsetHeight); //constructor
    ~Field(void) {} //destructor

    void GenerateField(void); //generating a set of bricks

    float GetWidth(void); //returns the width of the field
    std::vector <std::shared_ptr<Brick>> GetBricksMatrix(void); //returns a set of bricks

    void SetMovingBrick(void); //adding a new moving brick to the field
    void SetBrickType(sf::Color& brickColor, int& brickHealth); //selection of the type of brick for its generation

    void MoveAllBricks(void); //movement of bricks on the playing field
    void BricksCollision(void); //collision check of moving bricks with each other
    bool CheckNewX(float posX, float posY); //checking the correctness of the created coordinates of the new brick
    int DeleteBrick(unsigned number, float &bonusX, float &bonusY); /*
    decrease in health of the brick and its subsequent removal, if health is zero*/

    bool EndOfGame(void); //if there are only red non-destructible bricks, then the end of the game

    void DrawField(std::shared_ptr <sf::RenderWindow> window); //draws all the bricks on the field
};