#include "Bishop.h"
#include <cstdlib>
#include <ctime>

Bishop::Bishop(std::string idStr, Position pos, Direction dir, int sizeVal, bool isAlive)
    : Bug(idStr, pos, dir, sizeVal)
{
    this->alive = isAlive;
    srand(static_cast<unsigned int>(time(nullptr)));
}

void Bishop::move()
{
    if (!alive) return;

    const int boardWidth = 10;
    const int boardHeight = 10;

    if (isWayBlocked(boardWidth, boardHeight))
    {
        // pick a new diagonal direction
        int r = (rand() % 4);
        direction = static_cast<Direction>(5 + r);
    }

    switch (direction)
    {
    case Direction::NorthEast:
        position.setX(position.getX() + 1);
        position.setY(position.getY() - 1);
        break;
    case Direction::NorthWest:
        position.setX(position.getX() - 1);
        position.setY(position.getY() - 1);
        break;
    case Direction::SouthEast:
        position.setX(position.getX() + 1);
        position.setY(position.getY() + 1);
        break;
    case Direction::SouthWest:
        position.setX(position.getX() - 1);
        position.setY(position.getY() + 1);
        break;
    default:
        break;
    }

    path.push_back(position);
}

void Bishop::markDead(const std::string& killer)
{
    alive = false;
    killerId = killer;
}

std::string Bishop::getKillerId() const
{
    return killerId;
}
