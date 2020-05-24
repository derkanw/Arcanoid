#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <string>
#include "ClassField.h"
#include "ClassBar.h"
#include "ClassBall.h"
#include "ClassBrick.h"
#include "Bonus.h"

float userWindowWidth = 500, userWindowHeight = 600;
int score = 0;

float fieldWindowWidth = userWindowWidth;
float fieldWindowHeight = 2 * userWindowHeight / 5;
float offsetHeight = userWindowHeight / 10;
unsigned numberBricksInRow = 6;
unsigned numberBricksInColumn = 3;

float ballRadius = userWindowWidth / 40;
float ballX = userWindowWidth / 2 - ballRadius;
float ballY = 17 * userWindowHeight / 20;

float barHeight = userWindowHeight / 40;
float barWidth = userWindowWidth / 4;
float barX = ballX - barWidth / 2 + ballRadius;
float barY = ballY + 2 * ballRadius;

void BonusesWork(std::shared_ptr <sf::RenderWindow> window, std::shared_ptr <Bar> bar, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field, std::vector <std::shared_ptr<Bonus>> bonusesMatrix)
{
    for (unsigned k = 0; k < bonusesMatrix.size(); k++)
    {
        bonusesMatrix[k]->DrawBonus(window);
        if (bonusesMatrix[k]->Move(userWindowHeight, bar, ball, field))
        {
            bonusesMatrix.erase(bonusesMatrix.begin() + k);
            break;
        }
    }
}

void CreateText(std::shared_ptr <sf::RenderWindow> window)
{
    sf::Font font;
    font.loadFromFile("Resources/font.ttf");

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize((unsigned)userWindowHeight/20);
    text.setPosition(userWindowWidth/50, userWindowHeight/30);
    text.setString("Score: " + std::to_string(score));

    window->draw(text);
}

int main()
{
    srand((unsigned)time(0));

    std::shared_ptr <sf::RenderWindow> window;
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode((unsigned)userWindowWidth, (unsigned)userWindowHeight), "Arcanoid");
    window->setFramerateLimit(10);

    std::shared_ptr <Field> field;
    field = std::make_shared<Field>(fieldWindowHeight, fieldWindowWidth, numberBricksInRow, numberBricksInColumn, offsetHeight);

    std::shared_ptr <Bar> bar;
    bar = std::make_shared <Bar>(barHeight, barWidth, barX, barY);

    std::shared_ptr <Ball> ball;
    ball = std::make_shared <Ball>(ballRadius, ballX, ballY);
    
    std::vector <std::shared_ptr<Bonus>> bonusesMatrix;

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear();

        bar->Move(userWindowWidth);

        ball->Move(bar, userWindowWidth);

        score += ball->BallOut(userWindowHeight, bar);
        ball-> CollisionWithWindow(userWindowWidth, offsetHeight);
        if (ball->CollisionWithShape(bar->GetHeight(), bar->GetWidth(), bar->GetPosX(), bar->GetPosY(), bar->GetBallStick()) == 2)
        {
            bar->SetBallStick(-1);
            ball->SetBarOffset(ball->GetPosX() - bar->GetPosX());
        }

        std::vector <std::shared_ptr<Brick>> bricksMatrix = field->GetBricksMatrix();
        for (unsigned k = 0; k < bricksMatrix.size(); k++)
            if (ball->CollisionWithShape(bricksMatrix[k]->GetHeight(), bricksMatrix[k]->GetWidth(), bricksMatrix[k]->GetPosX(), bricksMatrix[k]->GetPosY())==1)
            {
                float bonusX = 0, bonusY = 0;
                if (bricksMatrix[k]->GetColor() == sf::Color::Cyan)
                    ball->SetSpeed(1.5, 1.5);
                score += field->DeleteBrick(k, bonusX, bonusY);
                if (bonusX!=0&&bonusY!=0)
                    switch (5)//rand() % 4)
                    {
                    case 0:
                        bonusesMatrix.push_back(std::make_shared<ChangeBar>(bonusX, bonusY));
                        break;
                    case 1:
                        bonusesMatrix.push_back(std::make_shared<ChangeBall>(bonusX, bonusY));
                        break;
                    case 2:
                        bonusesMatrix.push_back(std::make_shared<BallStick>(bonusX, bonusY));
                        break;
                    case 3:
                        bonusesMatrix.push_back(std::make_shared<BallBottom>(bonusX, bonusY));
                        break;
                    case 4:
                        bonusesMatrix.push_back(std::make_shared<RandomPath>(bonusX, bonusY));
                        break;
                    case 5:
                        bonusesMatrix.push_back(std::make_shared<MovingBrickBonus>(bonusX, bonusY));
                        break;
                    }
                break;
            }


        BonusesWork(window, bar, ball, field, bonusesMatrix);
        field->MoveAllBricks();
        field->BricksCollision();

        field->DrawField(window);
        ball->DrawBall(window);
        bar->DrawBar(window);
        CreateText(window);

        window->display();
    }

    return 0;
}