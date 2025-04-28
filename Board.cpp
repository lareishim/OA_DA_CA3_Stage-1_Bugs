#include "Board.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <iomanip>
#include <typeinfo>
#include "Crawler.h"
#include "Bishop.h"
#include "Hopper.h"

using namespace std;

Board::Board(int width, int height) : width(width), height(height)
{
}

Board::~Board()
{
    for (Bug* bug : bugs)
        delete bug;
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

    string type, id, directionStr;
    int x, y, size, hopLength;
    bool alive;

    cout << "Loading bugs from " << filename << endl;

    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        iss >> type >> id >> x >> y >> directionStr >> size >> boolalpha >> alive;

        if (type == "Crawler")
        {
            Position pos(x, y);
            Direction dirEnum = stringToDirection(directionStr);
            Bug* bug = new Crawler(id, pos, dirEnum, size, alive);
            bugs.push_back(bug);
        }
        else if (type == "Bishop")
        {
            Position pos(x, y);
            Direction dirEnum = stringToDirection(directionStr);
            Bug* bug = new Bishop(id, pos, dirEnum, size, alive);
            bugs.push_back(bug);
        }
        else if (type == "Hopper")
        {
            iss >> hopLength;  // Hopper has an extra field
            Position pos(x, y);
            Direction dirEnum = stringToDirection(directionStr);
            Bug* bug = new Hopper(id, pos, dirEnum, size, hopLength);
            bug->setAlive(alive);  // setAlive if needed depending on constructor
            bugs.push_back(bug);
        }
        else
        {
            cerr << "Failed to parse line: " << line << endl;
        }
    }

    file.close();
    cout << "Done loading: " << bugs.size() << " bugs loaded.\n";
}

void Board::displayAllBugs() const
{
    for (const auto& bug : bugs)
    {
        string type;
        if (dynamic_cast<Crawler*>(bug)) type = "Crawler";
        else if (dynamic_cast<Bishop*>(bug)) type = "Bishop";
        else if (dynamic_cast<Hopper*>(bug)) type = "Hopper";
        else type = "Unknown";

        cout << bug->getId() << " " << type << " ("
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
        case Direction::NorthEast: cout << "NorthEast";
            break;
        case Direction::NorthWest: cout << "NorthWest";
            break;
        case Direction::SouthEast: cout << "SouthEast";
            break;
        case Direction::SouthWest: cout << "SouthWest";
            break;
        }

        cout << " " << (bug->isAlive() ? "Alive" : "Dead") << endl;
    }
}

void Board::findBugById(const string& id) const
{
    for (const auto& bug : bugs)
    {
        if (bug->getId() == id)
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
                    bug->markDead(biggest->getId());
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
