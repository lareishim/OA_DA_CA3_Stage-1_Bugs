#ifndef BISHOP_H
#define BISHOP_H

#include "Bug.h"

class Bishop : public Bug
{
public:
    Bishop(std::string idStr, Position pos, Direction dir, int sizeVal, bool isAlive);
    void move() override;
    void markDead(const std::string& killer) override;
    std::string getKillerId() const ;
};

#endif
