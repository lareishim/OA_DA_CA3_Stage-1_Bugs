#include "Hopper.h"
#include <cstdlib>
#include <ctime>

Hopper::Hopper(int id, Position pos, Direction dir, int size, int hopLength)
    : Bug(id, pos, dir, size), hopLength(hopLength)
{
}

void Hopper::move()
{
    if (!alive) return;

    const int boardWidth = 10;
    const int boardHeight = 10;

    int hopCount = 0;
    while (hopCount < hopLength)
    {
        if (isWayBlocked(boardWidth, boardHeight))
        {
            direction = static_cast<Direction>((rand() % 4) + 1);
            continue; // Try new direction
        }

        // Move 1 unit in direction
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
        path.push_back(position);
        hopCount++;
    }
}
