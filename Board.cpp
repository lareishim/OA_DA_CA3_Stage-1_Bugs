//
// Created by larem on 01/04/2025.
//

#include "Board.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <ctime>
#include <iomanip>

using namespace std;

Board::Board(int width, int height) : width(width), height(height) {}

Board::~Board() {
    for (Crawler* crawler : crawlers) {
        delete crawler;
    }
    crawlers.clear();
}

void Board::loadCrawlersFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open file: " << filename << endl;
        return;
    }

    string id, direction;
    int x, y, size;
    bool alive;

    while (file >> id >> x >> y >> direction >> size >> boolalpha >> alive) {
        Position pos(x, y);
        Crawler* crawler = new Crawler(id, pos, direction[0], size, alive);
        crawlers.push_back(crawler);
    }

    file.close();
}

void Board::displayAllBugs() const {
    for (const auto& crawler : crawlers) {
        cout << crawler->getId() << " Crawler ("
             << crawler->getPosition().x << ","
             << crawler->getPosition().y << ") "
             << crawler->getSize() << " ";

        switch (crawler->getDirection()) {
            case Direction::North: cout << "North"; break;
            case Direction::East:  cout << "East";  break;
            case Direction::South: cout << "South"; break;
            case Direction::West:  cout << "West";  break;
        }

        cout << " " << (crawler->isAlive() ? "Alive" : "Dead") << endl;
    }
}

void Board::findBugById(const string& id) const {
    for (const auto& crawler : crawlers) {
        if (crawler->getId() == id) {
            cout << crawler->getId() << " Crawler ("
                 << crawler->getPosition().x << "," << crawler->getPosition().y << ") "
                 << crawler->getSize() << " ";

            switch (crawler->getDirection()) {
                case Direction::North: cout << "North"; break;
                case Direction::East:  cout << "East"; break;
                case Direction::South: cout << "South"; break;
                case Direction::West:  cout << "West"; break;
            }

            cout << " " << (crawler->isAlive() ? "Alive" : "Dead") << endl;
            return;
        }
    }

    cout << "bug " << id << " not found" << endl;
}

void Board::move() {
    for (auto& crawler : crawlers) {
        if (crawler->isAlive()) {
            crawler->move(width, height);
        }
    }

    map<pair<int, int>, vector<Crawler*>> cellMap;

    for (auto& crawler : crawlers) {
        if (crawler->isAlive()) {
            auto pos = crawler->getPosition();
            cellMap[{pos.x, pos.y}].push_back(crawler);
        }
    }


    for (auto& [pos, bugsInCell] : cellMap) {
        if (bugsInCell.size() > 1) {
            Crawler* biggest = bugsInCell[0];
            for (auto* bug : bugsInCell) {
                if (bug->getSize() > biggest->getSize()) {
                    biggest = bug;
                }
            }

            for (auto* bug : bugsInCell) {
                if (bug != biggest) {
                    bug->markDead(biggest->getId());
                }
            }
        }
    }
}

void Board::displayAllPaths() const {
    for (const auto& crawler : crawlers) {
        cout << crawler->getId() << " Crawler Path: ";
        for (auto it = crawler->getPath().begin(); it != crawler->getPath().end(); ++it) {
            cout << "(" << it->x << "," << it->y << ")";
            if (next(it) != crawler->getPath().end()) cout << ",";
        }

        if (!crawler->isAlive()) {
            if (!crawler->getKillerId().empty()) {
                cout << " Eaten by " << crawler->getKillerId();
            } else {
                cout << " Dead";
            }
        } else {
            cout << " Still alive";
        }

        cout << endl;
    }
}

void Board::savePathsToFile() const {
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);

    ostringstream filename;
    filename << "bugs_life_history_"
             << put_time(localTime, "%Y-%m-%d_%H-%M-%S")
             << ".out";

    ofstream out(filename.str());

    for (const auto& crawler : crawlers) {
        out << crawler->getId() << " Crawler Path: ";
        for (auto it = crawler->getPath().begin(); it != crawler->getPath().end(); ++it) {
            out << "(" << it->x << "," << it->y << ")";
            if (next(it) != crawler->getPath().end()) out << ",";
        }

        if (!crawler->isAlive()) {
            if (!crawler->getKillerId().empty()) {
                out << " Eaten by " << crawler->getKillerId();
            } else {
                out << " Dead";
            }
        } else {
            out << " Still alive";
        }

        out << endl;
    }

    out.close();
    cout << "Life history saved to: " << filename.str() << endl;
}

