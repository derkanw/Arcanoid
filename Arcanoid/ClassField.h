#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <memory>
#include "ClassBrick.h"
#include "Bonus.h"

class Field
{
private:
    float height, width;
    unsigned bricksInRow, bricksInColumn;

    unsigned score;

    std::vector <std::shared_ptr<Brick>> bricksMatrix;
    std::vector <std::shared_ptr<Bonus>> bonusesMatrix;

    std::array <sf::Color, 3> colorsMatrix = { sf::Color::Green, sf::Color::Red, sf::Color::Cyan };

public:
    Field(float fieldWindowHeight, float fieldWindowWidth, unsigned numberBricksInRow, unsigned numberBricksInColumn, float offsetHeight);
    ~Field(void) {}

    float GetHeight(void);
    float GetWidth(void);

    std::vector <std::shared_ptr<Brick>> GetBricksMatrix(void);

    void SetBrickType(sf::Color& brickColor, int& brickHealth);
    void GenerateField(float offsetHeight);

    int DeleteBrick(unsigned number);
    void BonusesWork(std::shared_ptr <sf::RenderWindow> window, float userWindowHeight, std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball);

    void DrawField(std::shared_ptr <sf::RenderWindow> window);
};