#include "GameLoop.h"
#include "ClassBrick.h"
#define INCREASE_SPEED (float)1.5
#define BONUS_NUMBER 6

GameLoop::GameLoop(void) //constructor
{
    userWindowWidth = 500;
    userWindowHeight = 600;
    score = 0;

    fieldWindowWidth = userWindowWidth;
    fieldWindowHeight = 2 * userWindowHeight / 5;
    offsetHeight = userWindowHeight / 10;
    numberBricksInRow = 6;
    numberBricksInColumn = 3;

    ballRadius = userWindowWidth / 40;
    ballX = userWindowWidth / 2 - ballRadius;
    ballY = 17 * userWindowHeight / 20;

    barHeight = userWindowHeight / 40;
    barWidth = userWindowWidth / 4;
    barX = ballX - barWidth / 2 + ballRadius;
    barY = ballY + 2 * ballRadius;

    window = std::make_shared<sf::RenderWindow>(sf::VideoMode((unsigned)userWindowWidth, (unsigned)userWindowHeight), "Arcanoid");
    window->setFramerateLimit(100);

    field = std::make_shared<Field>(fieldWindowHeight, fieldWindowWidth, numberBricksInRow, numberBricksInColumn, offsetHeight);
    bar = std::make_shared <Bar>(barHeight, barWidth, barX, barY);
    ball = std::make_shared <Ball>(ballRadius, ballX, ballY);
}

void GameLoop::StickingWork(void) //implements the work of sticking the ball to the bar
{
    if (ball->CollisionWithShape(bar->GetHeight(), bar->GetWidth(), bar->GetPosX(), bar->GetPosY(), bar->GetBallStick()) == 2)
    {
        bar->SetBallStick(-1);
        ball->SetBarOffset(ball->GetPosX() - bar->GetPosX());
    }
}

void GameLoop::ChooseBonus(float bonusX, float bonusY) //choosing type of bonus for working
{
    switch (rand() % BONUS_NUMBER)
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
}

void GameLoop::CollisionWithBricks(void) /*implements a check for the stocking of the ball with bricks
and the loss of the bonus when removing the bricks*/
{
    std::vector <std::shared_ptr<Brick>> bricksMatrix = field->GetBricksMatrix();
    float brickHeight, brickWidth, brickPosX, brickPosY;
    sf::Color brickColor;

    for (unsigned k = 0; k < bricksMatrix.size(); k++)
    {
        brickHeight = bricksMatrix[k]->GetHeight();
        brickWidth = bricksMatrix[k]->GetWidth();
        brickPosX = bricksMatrix[k]->GetPosX();
        brickPosY = bricksMatrix[k]->GetPosY();
        brickColor = bricksMatrix[k]->GetColor();

        if (ball->CollisionWithShape(brickHeight, brickWidth, brickPosX, brickPosY) == 1)
        {
            float bonusX = 0, bonusY = 0;

            if (brickColor == sf::Color::Cyan)
                ball->SetSpeed(INCREASE_SPEED, INCREASE_SPEED);

            score += field->DeleteBrick(k, bonusX, bonusY);

            if (bonusX != 0 && bonusY != 0)
                ChooseBonus(bonusX, bonusY);
            break;
        }
    }
}

void GameLoop::AllMovement(void) //implements all the movement in the gameplay
{
    bar->Move(userWindowWidth);
    field->MoveAllBricks();
    ball->Move(bar, userWindowWidth);
}

void GameLoop::AllColisions(void) //checks all collisions in the gameplay
{
    score += ball->BallOut(userWindowHeight, bar);
    ball->CollisionWithWindow(userWindowWidth, offsetHeight);
    StickingWork();
    CollisionWithBricks();
    field->BricksCollision();
}

void GameLoop::AllDrawing(void) //draws all the elements of the gameplay
{
    field->DrawField(window);
    ball->DrawBall(window);
    bar->DrawBar(window);
    CreateText();
}

void GameLoop::Start(void) //main cycle of the gameplay
{
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear();

        AllMovement();
        AllColisions();
        BonusesWork();
        AllDrawing();
        End();

        window->display();
    }
}

void GameLoop::BonusesWork(void) //bonus life cycle with drawing, movement and hitting the bar
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

void GameLoop::CreateText(void) //displays the score
{
    sf::Font font;
    font.loadFromFile("Resources/font.ttf");

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize((unsigned)userWindowHeight / 20);
    text.setPosition(userWindowWidth / 50, userWindowHeight / 30);
    text.setString("Score: " + std::to_string(score));

    window->draw(text);
}

void GameLoop::End(void) //if the game is over
{
    if (field->EndOfGame())
    {
        sf::Texture texture;
        if (score >= 0)
            texture.loadFromFile("Resources/win.png");
        else
            texture.loadFromFile("Resources/lose.png");

        sf::RectangleShape shape(sf::Vector2f(userWindowWidth, fieldWindowHeight));
        shape.setPosition(0, offsetHeight);
        shape.setTexture(&texture);

        window->draw(shape);
        window->display();

        sf::Clock timer;
        while (timer.getElapsedTime().asSeconds() < 3);

        window->close();
    }
}