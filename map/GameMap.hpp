#ifndef FMI_COURCE_PROJECT_DND_GAMEMAP_HPP
#define FMI_COURCE_PROJECT_DND_GAMEMAP_HPP

#include <iostream>
#include <map>
#include <string>
#include "../item/Item.hpp"
#include "../monster/Monster.hpp"
#include "../character/Character.hpp"

enum class TileType { WALL, EMPTY, CHARACTER, ITEM, MONSTER };
enum class Direction {UP, RIGHT, DOWN, LEFT};

struct MapTile {
    TileType type;
    friend std::ostream& operator<<(std::ostream& os, const MapTile& mapTile);
    friend std::istream& operator>>(std::istream& is, MapTile& mapTile);
};

inline std::ostream& operator<<(std::ostream& os, const MapTile& mapTile) {
    switch(mapTile.type) {
        case TileType::WALL:
            return os << "#";
        case TileType::EMPTY:
            return os << ".";
        case TileType::CHARACTER:
            return os << "C";
        case TileType::ITEM:
            return os << "T";
        case TileType::MONSTER:
            return os << "M";
    }
    return os;
}

inline std::istream& operator>>(std::istream& is, MapTile& mapTile) {
    char a;
    is >> a;
    switch(a) {
        case '#':
            mapTile.type = TileType::WALL;
            break;
        case '.':
            mapTile.type = TileType::EMPTY;
            break;
        case 'C':
            mapTile.type = TileType::CHARACTER;
            break;
        case 'T':
            mapTile.type = TileType::ITEM;
            break;
        case 'M':
            mapTile.type = TileType::MONSTER;
            break;
        default:
            throw std::invalid_argument("Type type not supported");
    }

    return is;
}

class GameMap {
public:
    GameMap(unsigned level, const Character& player);
    GameMap(const Character& player, unsigned int level, const std::string& path = "../map_assets/example.txt");
    void render();
    void movePlayer(Direction dir);

    ~GameMap();
private:
    size_t width, height;
    MapTile** map;
    std::map<std::pair<size_t, size_t >, Item*> items;
    std::map<std::pair<size_t, size_t >, Monster> monsters;
    Character player;
    size_t characterX, characterY;

    void readMapFromFile(const std::string &basicString);
    void setCharacterStartCoords();
    void setStartingMonsters(unsigned int level);
    void setStartingItems();
};



#endif
