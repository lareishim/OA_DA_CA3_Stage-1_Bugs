#include "Board.h"
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
using namespace std;

void menu(Board& board);

int main()
{
    Board board(10, 10);
    menu(board);
    return 0;
}

void menu(Board& board)
{
    int choice;
    bool exit = false;

    while (!exit)
    {
        cout << "\n--- Bug Board Menu ---\n";
        cout << "1. Initialize Bug Board (load data from file)\n";
        cout << "2. Display all Bugs\n";
        cout << "3. Find a Bug (given an id)\n";
        cout << "4. Tap the Bug Board (cause all to move, then fight/eat)\n";
        cout << "5. Display Life History of all Bugs (path taken)\n";
        cout << "6. Display all Cells listing their Bugs\n";
        cout << "7. Run simulation (generates a Tap every tenth of a second)\n";
        cout << "8. Exit (write Life History of all Bugs to file)\n";

        while (true)
        {
            cout << "Enter your choice (1–8): ";
            string input;
            getline(cin, input);
            stringstream ss(input);
            if (ss >> choice && ss.eof() && choice >= 1 && choice <= 8)
            {
                break;
            }
            else
            {
                cout << "Invalid input. Please enter a number between 1 and 8.\n";
            }
        }

        switch (choice)
        {
        case 1:
            board.loadCrawlersFromFile("crawler-bugs.txt");
            cout << "Bug board initialized.\n";
            break;
        case 2:
            board.displayAllBugs();
            break;
        case 3:
            {
                cout << "Enter bug ID to search: ";
                string id;
                getline(cin, id);
                board.findBugById(id);
                break;
            }
        case 4:
            board.move(); // One tap (move + fight)
            cout << "Board tapped. Bugs moved and resolved fights.\n";
            break;
        case 5:
            board.displayAllPaths();
            break;
        case 6:
            board.displayAllCells();
            break;
        case 7:

            break;
        case 8:
            board.savePathsToFile();
            cout << "Exiting.\n";
            exit = true;
            break;
        }
    }
}
