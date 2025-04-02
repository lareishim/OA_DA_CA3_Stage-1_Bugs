#ifndef CRAWLER_H
#define CRAWLER_H

#include "Position.h"
#include <list>
#include <string>

enum class Direction {
    North = 1,
    East,
    South,
    West
};

class Crawler {
private:
    std::string id;
    Position position;
    Direction direction;
    int size;
    bool alive;
    std::list<Position> path;

public:
    Crawler(std::string id, Position pos, char dirChar, int size, bool alive); // updated constructor

    std::string getId() const;
    Position getPosition() const;
    Direction getDirection() const;
    int getSize() const;
    bool isAlive() const;
    const std::list<Position>& getPath() const;

    void move(int boardWidth, int boardHeight);
    bool isWayBlocked(int boardWidth, int boardHeight) const;
    void markDead();
};

#endif // CRAWLER_H
