#ifndef POSITION_H
#define POSITION_H

struct Position
{
    int x;
    int y;

    Position(int x = 0, int y = 0) : x(x), y(y)
    {
    }

    bool operator==(const Position& other) const
    {
        return x == other.x && y == other.y;
    }

    int getX() const { return x; }
    int getY() const { return y; }

    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
};

#endif // POSITION_H
