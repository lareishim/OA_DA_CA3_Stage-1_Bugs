#include "Board.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <ctime>
#include <iomanip>
#include <typeinfo>

#include "Crawler.h"

using namespace std;

Board::Board(int width, int height) : width(width), height(height)
{
}

Board::~Board()
{
    for (Bug* bug : bugs)
    {
        delete bug;
    }
    bugs.clear();
}

void Board::loadCrawlersFromFile(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Could not open file: " << filename << endl;
        return;
    }

    string id, direction;
    int x, y, size;
    bool alive;

    while (file >> id >> x >> y >> direction >> size >> boolalpha >> alive)
    {
        Position pos(x, y);
        Bug* crawler = new Crawler(id, pos, direction[0], size, alive);
        bugs.push_back(crawler);
    }

    file.close();
}

void Board::displayAllBugs() const
{
    for (const auto& bug : bugs)
    {
        cout << bug->getId() << " " << typeid(*bug).name() << " ("
            << bug->getPosition().x << "," << bug->getPosition().y << ") "
            << bug->getSize() << " ";

        switch (bug->getDirection())
        {
        case Direction::North: cout << "North";
            break;
        case Direction::East: cout << "East";
            break;
        case Direction::South: cout << "South";
            break;
        case Direction::West: cout << "West";
            break;
        }

        cout << " " << (bug->isAlive() ? "Alive" : "Dead") << endl;
    }
}

void Board::findBugById(const string& id) const
{
    for (const auto& bug : bugs)
    {
        if (to_string(bug->getId()) == id)
        {
            cout << bug->getId() << " (" << bug->getPosition().x << "," << bug->getPosition().y << ") "
                << bug->getSize() << " ";

            switch (bug->getDirection())
            {
            case Direction::North: cout << "North";
                break;
            case Direction::East: cout << "East";
                break;
            case Direction::South: cout << "South";
                break;
            case Direction::West: cout << "West";
                break;
            }

            cout << " " << (bug->isAlive() ? "Alive" : "Dead") << endl;
            return;
        }
    }

    cout << "bug " << id << " not found" << endl;
}

void Board::move()
{
    for (auto& bug : bugs)
    {
        if (bug->isAlive())
        {
            bug->move();
        }
    }

    map<pair<int, int>, vector<Bug*>> cellMap;

    for (auto& bug : bugs)
    {
        if (bug->isAlive())
        {
            auto pos = bug->getPosition();
            cellMap[{pos.x, pos.y}].push_back(bug);
        }
    }

    for (auto& [pos, bugsInCell] : cellMap)
    {
        if (bugsInCell.size() > 1)
        {
            Bug* biggest = bugsInCell[0];
            for (auto* bug : bugsInCell)
            {
                if (bug->getSize() > biggest->getSize())
                {
                    biggest = bug;
                }
            }

            for (auto* bug : bugsInCell)
            {
                if (bug != biggest)
                {
                    // bug->markDead(biggest->getId()); ERROR
                }
            }
        }
    }
}

void Board::displayAllPaths() const
{
    for (const auto& bug : bugs)
    {
        cout << bug->getId() << " Path: ";
        for (auto it = bug->getPath().begin(); it != bug->getPath().end(); ++it)
        {
            cout << "(" << it->x << "," << it->y << ")";
            if (next(it) != bug->getPath().end()) cout << ",";
        }

        if (!bug->isAlive())
        {
            if (!bug->getKillerId().empty())
            {
                cout << " Eaten by " << bug->getKillerId();
            }
            else
            {
                cout << " Dead";
            }
        }
        else
        {
            cout << " Still alive";
        }

        cout << endl;
    }
}

void Board::savePathsToFile() const
{
    ostringstream filename;
    filename << "bugs_life_history_" << ".out";

    ofstream out(filename.str());

    for (const auto& bug : bugs)
    {
        out << bug->getId() << " Path: ";
        for (auto it = bug->getPath().begin(); it != bug->getPath().end(); ++it)
        {
            out << "(" << it->x << "," << it->y << ")";
            if (next(it) != bug->getPath().end()) out << ",";
        }

        if (!bug->isAlive())
        {
            if (!bug->getKillerId().empty())
            {
                out << " Eaten by " << bug->getKillerId();
            }
            else
            {
                out << " Dead";
            }
        }
        else
        {
            out << " Still alive";
        }

        out << endl;
    }

    out.close();
    cout << "Life history saved to: " << filename.str() << endl;
}

void Board::displayAllCells() const
{
    map<pair<int, int>, vector<const Bug*>> cellMap;

    for (const auto& bug : bugs)
    {
        Position pos = bug->getPosition();
        cellMap[{pos.x, pos.y}].push_back(bug);
    }

    cout << "--- Board Cells with Bugs ---" << endl;

    for (const auto& [pos, bugsInCell] : cellMap)
    {
        cout << "Cell (" << pos.first << "," << pos.second << "): ";
        for (const auto* bug : bugsInCell)
        {
            cout << bug->getId();
            if (!bug->isAlive()) cout << " (Dead)";
            cout << "  ";
        }
        cout << endl;
    }
}
