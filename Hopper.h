#ifndef HOPPER_H
#define HOPPER_H

#include "Bug.h"

class Hopper : public Bug
{
private:
    int hopLength;

public:
    Hopper(std::string id, Position pos, Direction dir, int size, int hopLength);
    void move() override;
};

#endif
