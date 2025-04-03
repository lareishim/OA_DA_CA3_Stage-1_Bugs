#include "Board.h"
#include <iostream>
using namespace std;

int main() {
    Board board(10, 10);  // Width = 10, Height = 10

    board.loadCrawlersFromFile("crawler-bugs.txt");

    std::cout << "--- Initial Crawlers ---" << std::endl;
    board.displayAllBugs();

    return 0;
}
