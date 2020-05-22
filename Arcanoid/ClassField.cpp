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

    GenerateField(offsetHeight);
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
            bricksMatrix.push_back(std::make_shared<Brick>( brickHeight, brickWidth, posX, posY, brickHealth, brickColor ));
        }
}

int Field::DeleteBrick(unsigned number)
{
    bricksMatrix[number]->SetHealth(MINUS_HEALTH);
    if (bricksMatrix[number]->GetHealth() == 0)
    {
        if (rand() % 100 < CHANCE_OF_BONUS)
        {
            switch (rand() % 2)
            {
            case 0:
                bonusesMatrix.push_back(std::make_shared<ChangeBar>(bricksMatrix[number]->GetPosX() + bricksMatrix[number]->GetWidth() / 2, bricksMatrix[number]->GetPosY() + bricksMatrix[number]->GetHeight()));
                break;
            case 1:
                bonusesMatrix.push_back(std::make_shared<ChangeBall>(bricksMatrix[number]->GetPosX() + bricksMatrix[number]->GetWidth() / 2, bricksMatrix[number]->GetPosY() + bricksMatrix[number]->GetHeight()));
                break;
            case 2:
                //bonusesMatrix.push_back(std::make_shared<Bonus>(bricksMatrix[number]->GetPosX() + bricksMatrix[number]->GetWidth() / 2, bricksMatrix[number]->GetPosY() + bricksMatrix[number]->GetHeight(), sf::Color::Yellow, 1));
                break;
            case 3:
                //bonusesMatrix.push_back(std::make_shared<Bonus>(bricksMatrix[number]->GetPosX() + bricksMatrix[number]->GetWidth() / 2, bricksMatrix[number]->GetPosY() + bricksMatrix[number]->GetHeight(), sf::Color::Yellow, 0));
                break;
            case 4:
                //bonusesMatrix.push_back(std::make_shared<Bonus>(bricksMatrix[number]->GetPosX() + bricksMatrix[number]->GetWidth() / 2, bricksMatrix[number]->GetPosY() + bricksMatrix[number]->GetHeight(), sf::Color::Yellow, 0));
                break;
            case 5:
                //bonusesMatrix.push_back(std::make_shared<Bonus>(bricksMatrix[number]->GetPosX() + bricksMatrix[number]->GetWidth() / 2, bricksMatrix[number]->GetPosY() + bricksMatrix[number]->GetHeight(), sf::Color::Yellow, 0));
                break;
            }
        }
        bricksMatrix.erase(bricksMatrix.begin() + number);
    }
    return 1;
}

void Field::BonusesWork(std::shared_ptr <sf::RenderWindow> window, float userWindowHeight, std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball)
{
    for (unsigned k = 0; k < bonusesMatrix.size(); k++)
    {
        bonusesMatrix[k]->DrawBonus(window);
        if (bonusesMatrix[k]->Move(userWindowHeight, bar, ball))
        {
            bonusesMatrix.erase(bonusesMatrix.begin() + k);
            break;
        }
    }
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