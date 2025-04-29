#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include "Bug.h"

class Board
{
private:
    std::vector<Bug*> bugs;
    int width, height;

public:
    Board(int width, int height);
    ~Board();

    void loadCrawlersFromFile(const std::string& filename);
    void displayAllBugs() const;
    void findBugById(const std::string& id) const;
    void move();
    void displayAllPaths() const;
    void savePathsToFile() const;
    void displayAllCells() const;

    const std::vector<Bug*>& getBugs() const;
};

#endif
