#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <memory>
#include "ClassBrick.h"

class Field
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
    Field(float fieldWindowHeight, float fieldWindowWidth, unsigned numberBricksInRow, unsigned numberBricksInColumn, float offsetHeight);
    ~Field(void) {}

    float GetHeight(void);
    float GetWidth(void);

    std::vector <std::shared_ptr<Brick>> GetBricksMatrix(void);

    void SetMovingBrick(void);
    void SetBrickType(sf::Color& brickColor, int& brickHealth);
    void GenerateField(void);

    void MoveAllBricks(void);
    bool CheckNewX(float posX, float posY);
    void BricksCollision(void);

    int DeleteBrick(unsigned number, float &bonusX, float &bonusY);

    bool EndOfGame(void);

    void DrawField(std::shared_ptr <sf::RenderWindow> window);
};