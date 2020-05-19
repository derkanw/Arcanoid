#include <SFML/Graphics.hpp>
#include <memory>
#include "ClassField.h"

unsigned userWindowWidth = 500, userWindowHeight = 600;
unsigned score = 0;

float fieldWindowWidth = (float)userWindowWidth;
float fieldWindowHeight = (float)userWindowHeight / 2;
float offsetHeight = (float)userWindowHeight / 10;
unsigned numberBricksInRow = 6;
unsigned numberBricksInColumn = 3;

std::shared_ptr <sf::RenderWindow> window;
std::shared_ptr <Field> field;


void CreateText(void)
{
    sf::Font font;
    font.loadFromFile("Resources/font.ttf");

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(userWindowHeight/20);
    text.setPosition((float)userWindowWidth/50, (float)userWindowHeight/30);

    text.setString("Score: " + std::to_string(score));
    window->draw(text);
}

int main()
{
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(userWindowWidth, userWindowHeight), "Arcanoid");
    window->setFramerateLimit(3);

    field = std::make_shared<Field>(fieldWindowHeight, fieldWindowWidth, numberBricksInRow, numberBricksInColumn, offsetHeight);

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear();

        field->DrawField(window);
        CreateText();

        window->display();
    }

    return 0;
}