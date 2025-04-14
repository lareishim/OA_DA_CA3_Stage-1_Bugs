#ifndef CRAWLER_H
#define CRAWLER_H

#include "Bug.h"
#include <string>

class Crawler : public Bug {
private:
    std::string killerId;

public:
    Crawler(std::string idStr, Position pos, char dirChar, int sizeVal, bool isAlive);

    void move() override; // Overrides Bug's pure virtual move()
    void markDead(const std::string& killer);

    std::string getKillerId() const;
};

#endif // CRAWLER_H

// we removed the other attributes since Crawler is now inheriting from the abstract class Bug,
// all of those attributes are already defined in the Bug class