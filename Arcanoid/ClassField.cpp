#include "ClassField.h"
#define CHANCE 15
#define CHANCE_OF_BONUS 50
#define MINUS_HEALTH -1

Field::Field(float fieldWindowHeight, float fieldWindowWidth, unsigned numberBricksInRow, unsigned numberBricksInColumn, float offsetHeight)
{
    height = fieldWindowHeight;
    width = fieldWindowWidth;
    bricksInRow = numberBricksInRow;
    bricksInColumn = numberBricksInColumn;
    offset = offsetHeight;
    numberMovingBricks = 0;

    GenerateField();
}

void Field::SetBrickType(sf::Color& brickColor, int& brickHealth)
{
    switch (rand() % CHANCE)
    {
    case 0:
    {
        brickColor = colorsMatrix[1];
        brickHealth = -1;
    }
        break;
    case 1:
    {
        brickColor = colorsMatrix[2];
        brickHealth = 1;
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

void Field::GenerateField(void)
{
    float brickHeight = height / bricksInColumn, brickWidth = width / bricksInRow;
    float posX = 0, posY = 0;
    sf::Color brickColor;
    int brickHealth;

    for (unsigned i = 0; i < bricksInColumn; i++)
        for (unsigned j = 0; j < bricksInRow; j++)
        {
            posX = j * brickWidth;
            posY = offset + i * brickHeight;
            SetBrickType(brickColor, brickHealth);
            bricksMatrix.push_back(std::make_shared<Brick>( brickHeight, brickWidth, posX, posY, brickHealth, brickColor ));
        }
}

int Field::DeleteBrick(unsigned number, float& bonusX, float& bonusY)
{
    bricksMatrix[number]->SetHealth(MINUS_HEALTH);
    if (bricksMatrix[number]->GetHealth() == 0)
    {
        if (rand() % 100 < CHANCE_OF_BONUS)
        {
            bonusX = bricksMatrix[number]->GetPosX() + bricksMatrix[number]->GetWidth() / 2;
            bonusY = bricksMatrix[number]->GetPosY() + bricksMatrix[number]->GetHeight();
        }
        if (bricksMatrix[number]->GetColor() == sf::Color::Magenta)
            numberMovingBricks -= 1;
        bricksMatrix.erase(bricksMatrix.begin() + number);
    }
    return 1;
}

void Field::MoveAllBricks(void)
{
    for (unsigned k = 0; k < bricksMatrix.size(); k++)
        bricksMatrix[k]->Move(width);
}

bool Field::CheckNewX(float posX, float posY)
{
    for (unsigned k = 0; k < bricksMatrix.size(); k++)
        if (bricksMatrix[k]->GetPosY() == posY)
            if (posX - bricksMatrix[k]->GetPosX() && posX <= bricksMatrix[k]->GetPosX() + bricksMatrix[k]->GetWidth() || posX >= width - bricksMatrix[k]->GetWidth())
                return false;
    return true;
}

void Field::SetMovingBrick(void)
{
    float randomX;
    float y = offset + height*(float)1.03;
    float brickWidth = width / bricksInRow;
    float brickHeight = height / bricksInColumn;

    if (numberMovingBricks < bricksInRow/2)
    {
        do
            randomX = (float)(rand() % (int)(width - brickWidth));
        while (!CheckNewX(randomX, y));

        bricksMatrix.push_back(std::make_shared <MovingBrick>(brickHeight, brickWidth, randomX, y));
        numberMovingBricks += 1;
    }
}

void Field::BricksCollision(void)
{
    for (unsigned i = 0; i < bricksMatrix.size(); i++)
        for (unsigned j = 0; j < bricksMatrix.size(); j++)
            if (i!=j && bricksMatrix[i]->GetColor() == sf::Color::Magenta && bricksMatrix[j]->GetColor() == sf::Color::Magenta)
                if ((fabs(bricksMatrix[i]->GetPosX() - (bricksMatrix[j]->GetPosX() + bricksMatrix[j]->GetWidth())) < abs(bricksMatrix[i]->GetSpeedX()))||
                    (fabs(bricksMatrix[i]->GetPosX() + bricksMatrix[i]->GetWidth() - bricksMatrix[j]->GetPosX()) < abs(bricksMatrix[i]->GetSpeedX())))
                    bricksMatrix[i]->SetSpeedX(-1);
}

bool Field::EndOfGame(void)
{
    for (unsigned k = 0; k < bricksMatrix.size(); k++)
        if (bricksMatrix[k]->GetColor() != sf::Color::Red)
            return false;
    return true;
}

std::vector <std::shared_ptr<Brick>> Field::GetBricksMatrix(void)
{
    return bricksMatrix;
}

float Field::GetHeight(void)
{
    return height;
}

float Field::GetWidth(void)
{
    return width;
}

void Field::DrawField(std::shared_ptr <sf::RenderWindow> window)
{
    for (unsigned k = 0; k < bricksMatrix.size(); k++)
        bricksMatrix[k]->DrawBrick(window);
}