#include "ClassField.h"

Field::Field(float fieldWindowHeight, float fieldWindowWidth, unsigned numberBricksInRow, unsigned numberBricksInColumn, float offsetHeight)
{
    height = fieldWindowHeight;
    width = fieldWindowWidth;
    bricksInRow = numberBricksInRow;
    bricksInColumn = numberBricksInColumn;

    GenerateField(offsetHeight);
}

void Field::GenerateField(float offsetHeight)
{
    float brickHeight = height / bricksInColumn, brickWidth = width / bricksInRow;
    float posX = 0, posY = 0;
    sf::Color brickColor = sf::Color::Green;
    int brickHealth = 1;

    for (unsigned i = 0; i < bricksInColumn; i++)
        for (unsigned j = 0; j < bricksInRow; j++)
        {
            posX = j * brickWidth;
            posY = offsetHeight + i * brickHeight;
            bricksMatrix.push_back({ brickHeight, brickWidth, posX, posY, brickHealth, brickColor });
        }
}

void Field::DrawField(std::shared_ptr <sf::RenderWindow> window)
{
    for (unsigned k = 0; k < bricksMatrix.size(); k++)
        bricksMatrix[k].DrawBrick(window);
}