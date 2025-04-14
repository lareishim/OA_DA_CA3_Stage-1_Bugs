#ifndef BUG_H
#define BUG_H

#include <vector>
#include "Position.h"

enum class Direction { North = 1, East, South, West };

class Bug
{
protected:
    int id;
    Position position;
    Direction direction;
    int size;
    bool alive;
    std::vector<Position> path;

public:
    Bug(int id, Position pos, Direction dir, int size)
        : id(id), position(pos), direction(dir), size(size), alive(true)
    {
        path.push_back(pos);
    }

    virtual ~Bug() = default;

    int getId() const { return id; }
    Position getPosition() const { return position; }
    Direction getDirection() const { return direction; }
    int getSize() const { return size; }
    bool isAlive() const { return alive; }
    const std::vector<Position>& getPath() const { return path; }

    void setAlive(bool a) { alive = a; }

    void setPosition(Position pos)
    {
        position = pos;
        path.push_back(pos);
    }

    virtual void move() = 0; // Pure virtual: must be implemented in derived classes

    bool isWayBlocked(int boardWidth, int boardHeight) const
    {
        int x = position.getX();
        int y = position.getY();

        switch (direction)
        {
        case Direction::North: return y == 0;
        case Direction::East: return x == boardWidth - 1;
        case Direction::South: return y == boardHeight - 1;
        case Direction::West: return x == 0;
        }
        return false;
    }
};

#endif
