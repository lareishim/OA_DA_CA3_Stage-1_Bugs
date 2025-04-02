#include "Board.h"
#include <iostream>

int main() {
    Board board(10, 10);  // Width = 10, Height = 10

    board.loadCrawlersFromFile("crawler-bugs.txt");

    std::cout << "--- Initial Crawlers ---" << std::endl;
    board.displayAllBugs();

    std::cout << "\n--- Crawlers After Tapping the Board ---" << std::endl;
    board.tapBoard();
    board.displayAllBugs();

    return 0;
}
