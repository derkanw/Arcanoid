#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include "ClassBrick.h"

class Field
{
private:
    float height, width;
    unsigned bricksInRow, bricksInColumn;

    unsigned score;

    std::vector <Brick> bricksMatrix;
    std::array <sf::Color, 3> colorsMatrix = { sf::Color::Green, sf::Color::Red, sf::Color::Cyan };

public:
    Field(float fieldWindowHeight, float fieldWindowWidth, unsigned numberBricksInRow, unsigned numberBricksInColumn, float offsetHeight);
    ~Field(void) {}

    std::vector <Brick> GetBricksMatrix(void);

    void SetBrickType(sf::Color& brickColor, int& brickHealth);
    void GenerateField(float offsetHeight);

    void DeleteBrick(unsigned number);

    void DrawField(std::shared_ptr <sf::RenderWindow> window);
};