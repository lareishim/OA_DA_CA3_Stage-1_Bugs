//
// Created by larem on 01/04/2025.
//

#include "Board.h"
#include <fstream>
#include <iostream>
#include <sstream>

Board::Board(int width, int height) : width(width), height(height) {}

Board::~Board() {
    for (Crawler* crawler : crawlers) {
        delete crawler;
    }
    crawlers.clear();
}

void Board::loadCrawlersFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filename << std::endl;
        return;
    }

    std::string id, direction;
    int x, y, size;
    bool alive;

    while (file >> id >> x >> y >> direction >> size >> std::boolalpha >> alive) {
        Position pos(x, y);
        Crawler* crawler = new Crawler(id, pos, direction[0], size, alive);
        crawlers.push_back(crawler);
    }

    file.close();
}

void Board::displayAllBugs() const {
    for (const auto& crawler : crawlers) {
        std::cout << crawler->getId() << " Crawler ("
                  << crawler->getPosition().x << ","
                  << crawler->getPosition().y << ") "
                  << crawler->getSize() << " ";

        switch (crawler->getDirection()) {
            case Direction::North: std::cout << "North"; break;
            case Direction::East:  std::cout << "East";  break;
            case Direction::South: std::cout << "South"; break;
            case Direction::West:  std::cout << "West";  break;
        }

        std::cout << " " << (crawler->isAlive() ? "Alive" : "Dead") << std::endl;
    }
}


void Board::move() {
    for (auto& crawler : crawlers) {
        crawler->move(width, height);
    }
}
