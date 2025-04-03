#include "Crawler.h"
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <iostream>

using namespace std;

Direction charToDirection(char c)
{
    switch (c)
    {
    case 'N': return Direction::North;
    case 'E': return Direction::East;
    case 'S': return Direction::South;
    case 'W': return Direction::West;
    default: throw invalid_argument("Invalid direction char");
    }
}

Crawler::Crawler(string id, Position pos, char dirChar, int size, bool alive)
    : id(id), position(pos), direction(charToDirection(dirChar)), size(size), alive(alive)
{
    path.push_back(pos);
    srand(time(nullptr));
}

string Crawler::getId() const { return id; }
Position Crawler::getPosition() const { return position; }
Direction Crawler::getDirection() const { return direction; }
int Crawler::getSize() const { return size; }
bool Crawler::isAlive() const { return alive; }
const list<Position>& Crawler::getPath() const { return path; }
string Crawler::getKillerId() const { return killerId; }

bool Crawler::isWayBlocked(int width, int height) const
{
    switch (direction)
    {
    case Direction::North: return position.y == 0;
    case Direction::East: return position.x == width - 1;
    case Direction::South: return position.y == height - 1;
    case Direction::West: return position.x == 0;
    }
    return true;
}

void Crawler::move(int width, int height)
{
    if (!alive) return;

    while (isWayBlocked(width, height))
    {
        direction = static_cast<Direction>((rand() % 4) + 1);
    }

    switch (direction)
    {
    case Direction::North: position.y--;
        break;
    case Direction::East: position.x++;
        break;
    case Direction::South: position.y++;
        break;
    case Direction::West: position.x--;
        break;
    }

    path.push_back(position);
}

void Crawler::markDead(const string& killer)
{
    alive = false;
    killerId = killer;
}
