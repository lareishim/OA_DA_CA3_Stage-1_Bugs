#ifndef BOARD_H
#define BOARD_H

#include "Bug.h"
#include <vector>
#include <string>

using namespace std;

class Board
{
private:
    int width;
    int height;
    vector<Bug*> bugs;

public:
    Board(int width, int height);
    ~Board();

    void loadCrawlersFromFile(const string& filename);
    void displayAllBugs() const;
    void findBugById(const string& id) const;
    void move();
    void displayAllPaths() const;
    void savePathsToFile() const;
    void displayAllCells() const;
};

#endif // BOARD_H
