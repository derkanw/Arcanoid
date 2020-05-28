#include "ClassField.h"
#define CHANCE 15
#define CHANCE_OF_BONUS 40
#define MINUS_HEALTH -1

Field::Field(float fieldWindowHeight, float fieldWindowWidth, unsigned numberBricksInRow,
    unsigned numberBricksInColumn, float offsetHeight) //constructor
{
    height = fieldWindowHeight;
    width = fieldWindowWidth;
    bricksInRow = numberBricksInRow;
    bricksInColumn = numberBricksInColumn;
    offset = offsetHeight;
    numberMovingBricks = 0;

    GenerateField();
}

void Field::SetBrickType(sf::Color& brickColor, int& brickHealth) //selection of the type of brick for its generation
{
    switch (rand() % CHANCE)
    {
    case 0: //indestructible brick
    {
        brickColor = colorsMatrix[1];
        brickHealth = -1;
    }
        break;
    case 1: //accelerating brick
    {
        brickColor = colorsMatrix[2];
        brickHealth = 1;
    }
        break;
    default: //regular brick
    {
        brickColor = colorsMatrix[0];
        brickHealth = 1;
    }
    break;
    }
}

void Field::GenerateField(void) //generating a set of bricks
{
    float brickHeight = height / bricksInColumn;
    float brickWidth = width / bricksInRow;
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

int Field::DeleteBrick(unsigned number, float& bonusX, float& bonusY) /*
decrease in health of the brick and its subsequent removal, if health is zero*/
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

void Field::MoveAllBricks(void) //movement of bricks on the playing field
{
    for (unsigned k = 0; k < bricksMatrix.size(); k++)
        bricksMatrix[k]->Move(width);
}

bool Field::CheckNewX(float posX, float posY) //checking the correctness of the created coordinates of the new brick
{
    float leftBoarder, rightBoarder, brickOut, brickPosY;

    for (unsigned k = 0; k < bricksMatrix.size(); k++)
    {
        brickPosY = bricksMatrix[k]->GetPosY();
        leftBoarder = bricksMatrix[k]->GetPosX() - bricksMatrix[k]->GetWidth();
        rightBoarder = bricksMatrix[k]->GetPosX() + bricksMatrix[k]->GetWidth();
        brickOut = width - bricksMatrix[k]->GetWidth();

        if (brickPosY == posY)
            if (posX >= leftBoarder && posX <= rightBoarder || posX >= brickOut)
                return false;
    }

    return true;
}

void Field::SetMovingBrick(void) //adding a new moving brick to the field
{
    float randomX;
    float y = offset + height*(float)1.03;
    float brickWidth = width / bricksInRow;
    float brickHeight = height / bricksInColumn;

    if (numberMovingBricks < bricksInRow / 2)
    {
        do
            randomX = (float)(rand() % (int)(width - brickWidth));
        while (!CheckNewX(randomX, y));

        bricksMatrix.push_back(std::make_shared <MovingBrick>(brickHeight, brickWidth, randomX, y));
        numberMovingBricks += 1;
    }
}

void Field::BricksCollision(void) //collision check of moving bricks with each other
{
    sf::Color brickColor1, brickColor2;
    float leftSide1, rightSide1, leftSide2, rightSide2;
    float speed;

    bool sameType, leftCollision, rightCollision;

    for (unsigned i = 0; i < bricksMatrix.size(); i++)
    {
        brickColor1 = bricksMatrix[i]->GetColor();
        leftSide1 = bricksMatrix[i]->GetPosX();
        rightSide1 = bricksMatrix[i]->GetPosX() + bricksMatrix[i]->GetWidth();
        speed = abs(bricksMatrix[i]->GetSpeedX());

        for (unsigned j = 0; j < bricksMatrix.size(); j++)
        {
            brickColor2 = bricksMatrix[j]->GetColor();
            leftSide2 = bricksMatrix[j]->GetPosX();
            rightSide2 = bricksMatrix[j]->GetPosX() + bricksMatrix[j]->GetWidth();

            sameType = (brickColor1 == sf::Color::Magenta) && (brickColor2 == sf::Color::Magenta);
            leftCollision = abs(leftSide1 - rightSide2) < speed;
            rightCollision = abs(rightSide1 - leftSide2) < speed;

            if ((i != j) && sameType && (leftCollision || rightCollision))
                bricksMatrix[i]->SetSpeedX(-1);
        }
    }
}

bool Field::EndOfGame(void) //if there are only red non-destructible bricks, then the end of the game
{
    for (unsigned k = 0; k < bricksMatrix.size(); k++)
        if (bricksMatrix[k]->GetColor() != sf::Color::Red)
            return false;
    return true;
}

float Field::GetWidth(void) //returns the width of the field
{
    return width;
}

std::vector <std::shared_ptr<Brick>> Field::GetBricksMatrix(void) //returns a set of bricks
{
    return bricksMatrix;
}

void Field::DrawField(std::shared_ptr <sf::RenderWindow> window) //draws all the bricks on the field
{
    for (unsigned k = 0; k < bricksMatrix.size(); k++)
        bricksMatrix[k]->DrawBrick(window);
}