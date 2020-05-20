#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "ClassField.h"
#include "ClassBar.h"
#include "ClassBall.h"

float userWindowWidth = 500, userWindowHeight = 600;
unsigned score = 0;
bool moving = false;

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

    ball->SetSpeed(10.f, -10.f);

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

        moving = ball->Move(userWindowHeight, userWindowWidth, offsetHeight, bar, field);

        field->DrawField(window);
        ball->DrawBall(window);
        bar->DrawBar(window);
        CreateText(window);

        window->display();
    }

    return 0;
}