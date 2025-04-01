#ifndef BOARD_H
#define BOARD_H

#include "Crawler.h"
#include <vector>
#include <string>

class Board
{
private:
    int width;
    int height;
    std::vector<Crawler*> crawlers;

public:
    Board(int width, int height);
    ~Board(); // To delete allocated Crawlers

    void loadCrawlersFromFile(const std::string& filename);
    void displayAllBugs() const;
    void findBugById(int id) const;
    void tapBoard(); // calls move() on all bugs
    void displayAllPaths() const;
    void savePathsToFile() const;
    void displayAllCells() const;
};

#endif // BOARD_H
