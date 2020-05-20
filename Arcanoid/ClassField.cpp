#include "ClassField.h"
#define CHANCE_OF_TERMINATOR 15
#define MINUS_HEALTH -1

Field::Field(float fieldWindowHeight, float fieldWindowWidth, unsigned numberBricksInRow, unsigned numberBricksInColumn, float offsetHeight)
{
    height = fieldWindowHeight;
    width = fieldWindowWidth;
    bricksInRow = numberBricksInRow;
    bricksInColumn = numberBricksInColumn;

    GenerateField(offsetHeight);
}

void Field::SetBrickType(sf::Color& brickColor, int& brickHealth)
{
    switch (rand() % CHANCE_OF_TERMINATOR)
    {
    case 0:
    {
        brickColor = colorsMatrix[1];
        brickHealth = -1;
    }
        break;
    default:
    {
        brickColor = colorsMatrix[0];
        brickHealth = 1;
    }
        break;
    }
}

void Field::GenerateField(float offsetHeight)
{
    float brickHeight = height / bricksInColumn, brickWidth = width / bricksInRow;
    float posX = 0, posY = 0;
    sf::Color brickColor;
    int brickHealth;

    for (unsigned i = 0; i < bricksInColumn; i++)
        for (unsigned j = 0; j < bricksInRow; j++)
        {
            posX = j * brickWidth;
            posY = offsetHeight + i * brickHeight;
            SetBrickType(brickColor, brickHealth);
            bricksMatrix.push_back({ brickHeight, brickWidth, posX, posY, brickHealth, brickColor });
        }
}

void Field::DeleteBrick(unsigned number)
{
    bricksMatrix[number].SetHealth(MINUS_HEALTH);
        if (bricksMatrix[number].GetHealth() == 0)
            bricksMatrix.erase(bricksMatrix.begin() + number);
}

std::vector <Brick> Field::GetBricksMatrix(void)
{
    return bricksMatrix;
}

void Field::DrawField(std::shared_ptr <sf::RenderWindow> window)
{
    for (unsigned k = 0; k < bricksMatrix.size(); k++)
        bricksMatrix[k].DrawBrick(window);
}