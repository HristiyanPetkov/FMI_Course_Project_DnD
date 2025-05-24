#ifndef FMI_COURSE_PROJECT_DND_GAMEMAP_HPP
#define FMI_COURSE_PROJECT_DND_GAMEMAP_HPP

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "Direction.hpp"
#include "../item/Item.hpp"
#include "../monster/Monster.hpp"
#include "../character/Character.hpp"
#include "tile/Tile.hpp"

class GameMap {
public:
    GameMap();
    explicit GameMap(unsigned level);
//    explicit GameMap(const std::string& path = "../map_assets/example.txt");
    GameMap(const GameMap& other);
    GameMap& operator=(const GameMap& other);
    ~GameMap();

    void render();
    void move(Character& character, Direction direction);
    bool onNextLevelField() const;
    void serialize(std::ostream &os) const;
    void deserialize(std::istream &is);
private:
    size_t width, height, numberOfMonsters, numberOfTreasures;
    std::vector<std::vector<Tile*>> map;
    size_t characterX, characterY;

    void swap(GameMap& other);
    void calculateLevelParameters(unsigned level);
    void fillMapWithEmptyAndWalls();
    void setStartingCharacterTile();
    void placeRandomElements(unsigned level);
    std::vector<std::pair<size_t, size_t>> getValidPositions();

    bool canMove(Direction direction);
    void movePlayer(Character& character, Direction direction);
};

#endif
