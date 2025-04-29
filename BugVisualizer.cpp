#include "BugVisualizer.h"
#include "Board.h"
#include "Bug.h"
#include "Crawler.h"
#include "Hopper.h"
#include "Bishop.h"
#include <SFML/System/Clock.hpp>

void BugVisualizer::run(Board& board)
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Bug Simulation");
    sf::Clock clock;
    sf::Time moveDelay = sf::milliseconds(700);

    int moveCount = 0;
    const int maxMoves = 30;

    float gridSize = 50.0f;
    float margin = 5.0f;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (clock.getElapsedTime() >= moveDelay && moveCount < maxMoves)
        {
            board.move();
            clock.restart();
            moveCount++;
        }

        if (moveCount >= maxMoves)
        {
            window.close();
        }

        window.clear(sf::Color::Black);

        const auto& bugs = board.getBugs();
        for (const auto* bug : bugs)
        {
            sf::CircleShape shape(10);
            shape.setPosition(
                bug->getPosition().x * gridSize + margin,
                bug->getPosition().y * gridSize + margin
            );

            if (!bug->isAlive())
            {
                shape.setFillColor(sf::Color(150, 0, 0));
            }
            else if (dynamic_cast<const Crawler*>(bug))
            {
                shape.setFillColor(sf::Color::Green);
            }
            else if (dynamic_cast<const Hopper*>(bug))
            {
                shape.setFillColor(sf::Color::Blue);
            }
            else if (dynamic_cast<const Bishop*>(bug))
            {
                shape.setFillColor(sf::Color::Magenta);
            }
            else
            {
                shape.setFillColor(sf::Color::White);
            }

            window.draw(shape);
        }

        window.display();
    }
}
