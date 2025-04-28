#include "Hopper.h"
#include <cstdlib>
#include <ctime>

Hopper::Hopper(string id, Position pos, Direction dir, int size, int hopLength)
    : Bug(id, pos, dir, size), hopLength(hopLength)
{
}

void Hopper::move()
{
    if (!alive) return;

    const int boardWidth = 10;
    const int boardHeight = 10;

    int hops = 0;
    while (hops < hopLength)
    {
        if (isWayBlocked(boardWidth, boardHeight))
        {
            direction = static_cast<Direction>((rand() % 4) + 1);
            continue;
        }

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
        default: break;
        }

        path.push_back(position);
        ++hops;
    }
}
