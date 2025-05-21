#include <fstream>
#include "GameMap.hpp"

GameMap::GameMap(unsigned int level, const Character& player)
: width(0), height(0), map(nullptr), items(), monsters(), player(player), characterX(0), characterY(0) {}

GameMap::GameMap(const Character& player, unsigned int level, const std::string &path)
: width(0), height(0), map(nullptr), items(), monsters(), player(player), characterX(0), characterY(0) {
    readMapFromFile(path);
    setCharacterStartCoords();
    setStartingMonsters(level);
    setStartingItems();
}

void GameMap::render() {
    for(size_t i = 0; i < width; ++i) {
        for (size_t j = 0; j < height; ++j) {
            std::cout << map[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << "Character coords: {" << characterX << ", " << characterY << "}" << std::endl;
    player.print();
    std::cout << "Monsters: " << std::endl;
    for(const auto& monster : monsters) {
        std::cout << monster.first.first << ", " << monster.first.second << ": ";
        monster.second.print();
    }
    for(const auto& item : items) {
        std::cout << item.first.first << ", " << item.first.second << ": ";
        item.second->print();
    }
}

void GameMap::movePlayer(Direction dir) {
//    if(playerCanMove(dir)) {
//        changePlayerCoords(dir);
//    }
}

void GameMap::readMapFromFile(const std::string &path) {
    std::ifstream file(path);
    file >> width >> height;
    std::cout << "Width: " << width;
    map = new MapTile*[width];
    for(size_t i = 0 ; i < width; ++i) {
        map[i] = new MapTile[height];
    }
    for(size_t i = 0; i < width; ++i) {
        for(size_t j = 0; j < height; ++j) {
            file >> map[i][j];
        }
    }
}

void GameMap::setCharacterStartCoords() {
    for(size_t i = 0; i < width; ++i) {
        for(size_t j = 0; j < height; ++j) {
            std::cout << map[i][j];
            if(map[i][j].type == TileType::CHARACTER) {
                characterX = i;
                characterY = j;
                return;
            }
        }
    }
    throw std::invalid_argument("Map doesn't contain a character");
}

void GameMap::setStartingMonsters(unsigned int level) {
    for(size_t i = 0; i < width; ++i) {
        for(size_t j = 0; j < height; ++j) {
            if(map[i][j].type == TileType::MONSTER) {
                std::pair<size_t, size_t> position = {i, j};
                monsters.emplace(std::make_pair(i, j), Monster("Dragon", level));
            }
        }
    }
}

void GameMap::setStartingItems() {
    for(size_t i = 0; i < width; ++i) {
        for(size_t j = 0; j < height; ++j) {
            if(map[i][j].type == TileType::ITEM) {
                std::pair<size_t, size_t> position = {i, j};
                items.emplace(std::make_pair(i, j), new Item("Basic", 10));
            }
        }
    }
}

GameMap::~GameMap() {
    for(auto& pair : items) {
        delete pair.second;
    }
    for(size_t i = 0; i < width; ++i) {
        delete [] map[i];
    }
    delete [] map;
}
