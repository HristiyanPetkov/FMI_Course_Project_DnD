#include <fstream>
#include <random>

#include "GameMap.hpp"
#include "tile/WallTile.hpp"
#include "tile/EmptyTile.hpp"
#include "tile/CharacterTile.hpp"
#include "tile/MonsterTile.hpp"
#include "tile/TreasureTile.hpp"

GameMap::GameMap()
: width(0), height(0), numberOfMonsters(0), numberOfTreasures(0), map(), characterX(0), characterY(0) {}

GameMap::GameMap(unsigned int level)
: width(10), height(10), numberOfMonsters(2), numberOfTreasures(2), map(), characterX(1), characterY(1) {
    calculateLevelParameters(level);
    map.resize(height, std::vector<Tile*>(width, nullptr));

    fillMapWithEmptyAndWalls();
    setStartingCharacterTile();
    placeRandomElements(level);
}

void GameMap::calculateLevelParameters(unsigned int level) {
    size_t width1 = 10, width2 = 15;
    size_t height1 = 10, height2 = 10;
    size_t numberOfMonsters1 = 2, numberOfMonsters2 = 3;
    size_t numberOfTreasures1 = 2, numberOfTreasures2 = 2;

    if(level == 0) {
        throw std::invalid_argument("Starting level need to be at least 1");
    }
    if(level == 1) {
        return;
    }
    for(unsigned i = 2; i < level; ++i) {
        width2 += width1;
        width1 = width2 - width1;

        height2 += height1;
        height1 = height2 - height1;

        numberOfMonsters2 += numberOfMonsters1;
        numberOfMonsters1 = numberOfMonsters2 - numberOfMonsters1;

        numberOfTreasures2 += numberOfTreasures1;
        numberOfTreasures1 = numberOfTreasures2 - numberOfTreasures1;
    }

    width = width2;
    height = height2;
    numberOfMonsters = numberOfMonsters2;
    numberOfTreasures = numberOfTreasures2;
}

void GameMap::fillMapWithEmptyAndWalls() {
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                map[i][j] = new WallTile();
            } else {
                map[i][j] = new EmptyTile();
            }
        }
    }
}

void GameMap::setStartingCharacterTile() {
    delete map[characterY][characterX];
    map[characterY][characterX] = new CharacterTile();
}

void GameMap::placeRandomElements(unsigned int level) {
    std::vector<std::pair<size_t, size_t>> validPositions = getValidPositions();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(validPositions.begin(), validPositions.end(), gen);

    for(size_t i = 0; i < numberOfMonsters; ++i) {
        auto [x, y] = validPositions.front();
        delete map[y][x];
        map[y][x] = new MonsterTile(Monster("Dragon", level));
        validPositions.erase(validPositions.begin());
    }
    for(size_t i = 0; i < numberOfTreasures; ++i) {
        auto [x, y] = validPositions.front();
        delete map[y][x];
        map[y][x] = TreasureTile::generateRandomTreasureTile(level);
        validPositions.erase(validPositions.begin());
    }
}

std::vector<std::pair<size_t, size_t>> GameMap::getValidPositions() {
    std::vector<std::pair<size_t, size_t>> validPositions;
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            if (map[y][x]->isEmpty()) {
                validPositions.emplace_back(x, y);
            }
        }
    }

    return validPositions;
}

GameMap::GameMap(const GameMap &other)
: width(other.width), height(other.height), numberOfMonsters(other.numberOfMonsters),
  numberOfTreasures(other.numberOfTreasures), map(),
  characterX(other.characterX), characterY(other.characterY) {
    map.resize(height, std::vector<Tile*>(width, nullptr));
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            if (other.map[y][x]) {
                map[y][x] = other.map[y][x]->clone();
            }
        }
    }
}

GameMap &GameMap::operator=(const GameMap &other) {
    GameMap copy(other);
    swap(copy);

    return *this;
}

void GameMap::swap(GameMap &other) {
    using std::swap;
    swap(width, other.width);
    swap(height, other.height);
    swap(numberOfMonsters, other.numberOfMonsters);
    swap(numberOfTreasures, other.numberOfTreasures);
    swap(map, other.map);
    swap(characterX, other.characterX);
    swap(characterY, other.characterY);
}

GameMap::~GameMap() {
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            delete map[y][x];
        }
    }
}

void GameMap::render() {
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            std::cout << map[y][x]->getDisplayCharacter();
        }
        std::cout << std::endl;
    }
    std::cout << "Character coords: {" << characterX << ", " << characterY << "}" << std::endl;
}

void GameMap::move(Character& character, Direction direction) {
    if(canMove(direction)) {
        movePlayer(character, direction);
    }
}

bool GameMap::canMove(Direction direction) {
    switch(direction) {
        case Direction::UP:
            if(map[characterY - 1][characterX]->getDisplayCharacter() != '#') {
                return true;
            }
            break;
        case Direction::RIGHT:
            if(map[characterY][characterX + 1]->getDisplayCharacter() != '#') {
                return true;
            }
            break;
        case Direction::DOWN:
            if(map[characterY + 1][characterX]->getDisplayCharacter() != '#') {
                return true;
            }
            break;
        case Direction::LEFT:
            if(map[characterY][characterX - 1]->getDisplayCharacter() != '#') {
                return true;
            }
            break;
    }

    return false;
}

void GameMap::movePlayer(Character& character, Direction direction) {
    switch(direction) {
        case Direction::UP:
            map[characterY - 1][characterX]->apply(character);
            map[characterY - 1][characterX] = map[characterY - 1][characterX]->changeOnExpended();
            std::swap(map[characterY - 1][characterX], map[characterY][characterX]);
            --characterY;
            break;
        case Direction::RIGHT:
            map[characterY][characterX + 1]->apply(character);
            map[characterY][characterX + 1] = map[characterY][characterX + 1]->changeOnExpended();
            std::swap(map[characterY][characterX + 1], map[characterY][characterX]);
            ++characterX;
            break;
        case Direction::DOWN:
            map[characterY + 1][characterX]->apply(character);
            map[characterY + 1][characterX] = map[characterY + 1][characterX]->changeOnExpended();
            std::swap(map[characterY + 1][characterX], map[characterY][characterX]);
            ++characterY;
            break;
        case Direction::LEFT:
            map[characterY][characterX - 1]->apply(character);
            map[characterY][characterX - 1] = map[characterY][characterX - 1]->changeOnExpended();
            std::swap(map[characterY][characterX - 1], map[characterY][characterX]);
            --characterX;
            break;
    }
}

bool GameMap::onNextLevelField() const {
    return characterY == height - 2 && characterX == width - 2;
}

void GameMap::serialize(std::ostream &os) {
    os << width << " " << height << " " << numberOfMonsters << " " << numberOfTreasures << " " << characterX << " " << characterY << std::endl;
    for(size_t y = 0; y < height; ++y) {
        for(size_t x = 0; x < width; ++x) {
            map[y][x]->serialize(os);
        }
    }
}

void GameMap::deserialize(std::istream &is) {
    GameMap newMap;
    is >> newMap.width >> newMap.height >> newMap.numberOfMonsters >> newMap.numberOfTreasures >> newMap.characterX >> newMap.characterY;
    newMap.map.resize(newMap.height, std::vector<Tile*>(newMap.width, nullptr));
    for(size_t y = 0; y < newMap.height; ++y) {
        for(size_t x = 0; x < newMap.width; ++x) {
            newMap.map[y][x] = Tile::deserialize(is);
        }
    }
    swap(newMap);
}

//width(10), height(10), numberOfMonsters(2), numberOfTreasures(2), map(), characterX(1), characterY(1)