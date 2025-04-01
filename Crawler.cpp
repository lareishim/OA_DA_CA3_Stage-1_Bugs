#include "Crawler.h"
#include <cstdlib>
#include <ctime>

Crawler::Crawler(int id, Position pos, Direction dir, int size)
    : id(id), position(pos), direction(dir), size(size), alive(true)
{
    path.push_back(pos);
    std::srand(std::time(nullptr));
}

int Crawler::getId() const { return id; }
Position Crawler::getPosition() const { return position; }
Direction Crawler::getDirection() const { return direction; }
int Crawler::getSize() const { return size; }
bool Crawler::isAlive() const { return alive; }
const std::list<Position>& Crawler::getPath() const { return path; }

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

    // Try to move; if blocked, pick a new direction until unblocked
    while (isWayBlocked(width, height))
    {
        direction = static_cast<Direction>((std::rand() % 4) + 1);
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

void Crawler::markDead()
{
    alive = false;
}
