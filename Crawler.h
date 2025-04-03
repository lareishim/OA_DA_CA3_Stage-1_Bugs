#ifndef CRAWLER_H
#define CRAWLER_H

#include "Position.h"
#include <list>
#include <string>

enum class Direction
{
    North = 1,
    East,
    South,
    West
};

class Crawler
{
private:
    std::string id;
    Position position;
    Direction direction;
    int size;
    bool alive;
    std::string killerId;
    std::list<Position> path;

public:
    Crawler(std::string id, Position pos, char dirChar, int size, bool alive);

    std::string getId() const;
    Position getPosition() const;
    Direction getDirection() const;
    int getSize() const;
    bool isAlive() const;
    std::string getKillerId() const;
    const std::list<Position>& getPath() const;

    void move(int boardWidth, int boardHeight);
    bool isWayBlocked(int boardWidth, int boardHeight) const;
    void markDead(const std::string& killer);
};

#endif // CRAWLER_H
