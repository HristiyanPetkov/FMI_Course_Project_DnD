#include "Tile.hpp"
#include "EmptyTile.hpp"
#include "WallTile.hpp"
#include "CharacterTile.hpp"
#include "MonsterTile.hpp"
#include "TreasureTile.hpp"

bool Tile::isEmpty() {
    return false;
}

Tile *Tile::changeOnExpended() {
    return this;
}

void Tile::serialize(std::ostream &os) const {
    os << getDisplayCharacter() << std::endl;
}

Tile* Tile::deserialize(std::istream &is) {
    char tileCharacter;
    Monster monster;
    ItemType type;
    Item* item;
    Tile* tile;
    is >> tileCharacter;
    switch(tileCharacter) {
        case '#':
            return new WallTile();
        case '.':
            return new EmptyTile();
        case 'C':
            return new CharacterTile();
        case 'M':
            monster.deserialize(is);
            return new MonsterTile(monster);
        case 'T':
            is >> type;
            item = Item::deserialize(is, type);
            tile = new TreasureTile(item, type);
            delete item;
            return tile;
        default:
            throw std::invalid_argument("Unsupported tile type");
    }
}
