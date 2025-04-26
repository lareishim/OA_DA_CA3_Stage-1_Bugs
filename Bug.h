#ifndef BUG_H
#define BUG_H

#include <vector>
#include <string>
#include "Position.h"

using namespace std;

enum class Direction { North = 1, East, South, West };

class Bug
{
protected:
    int id;
    Position position;
    Direction direction;
    int size;
    bool alive;
    vector<Position> path;
    string killerId; // 🔥 Add this to support Board.cpp

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
    const vector<Position>& getPath() const { return path; }
    string getKillerId() const { return killerId; } // 🔥 Add this
    void markDead(const string& killer)
    {
        // 🔥 And this
        alive = false;
        killerId = killer;
    }

    void setAlive(bool a) { alive = a; }

    void setPosition(Position pos)
    {
        position = pos;
        path.push_back(pos);
    }

    virtual void move() = 0; // Pure virtual

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
