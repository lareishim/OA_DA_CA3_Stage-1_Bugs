#include "Crawler.h"
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <iostream>

using namespace std;

Direction stringToDirection(const string& dir)
{
    if (dir == "N") return Direction::North;
    if (dir == "E") return Direction::East;
    if (dir == "S") return Direction::South;
    if (dir == "W") return Direction::West;
    if (dir == "NE") return Direction::NorthEast;
    if (dir == "NW") return Direction::NorthWest;
    if (dir == "SE") return Direction::SouthEast;
    if (dir == "SW") return Direction::SouthWest;

    throw invalid_argument("Invalid direction string: " + dir);
}

// Constructor
Crawler::Crawler(string idStr, Position pos, Direction dir, int sizeVal, bool isAlive)
    : Bug(idStr, pos, dir, sizeVal)
{
    this->alive = isAlive;
    srand(time(nullptr));
}

// Override of abstract move() method
void Crawler::move()
{
    if (!alive) return;

    const int boardWidth = 10;
    const int boardHeight = 10;

    // Keep changing direction until not blocked
    while (isWayBlocked(boardWidth, boardHeight))
    {
        direction = static_cast<Direction>((rand() % 4) + 1);
    }

    // Move according to direction
    switch (direction)
    {
    case Direction::North: position.setY(position.getY() - 1);
        break;
    case Direction::East: position.setX(position.getX() + 1);
        break;
    case Direction::South: position.setY(position.getY() + 1);
        break;
    case Direction::West: position.setX(position.getX() - 1);
        break;
    }

    path.push_back(position); // Record new position
}

// Mark the crawler as dead and store killer ID
void Crawler::markDead(const string& killer)
{
    alive = false;
    killerId = killer;
}

// Getter for killerId
string Crawler::getKillerId() const
{
    return killerId;
}
