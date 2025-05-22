#include "WallTile.hpp"

void WallTile::apply(Character &character) {}

char WallTile::getDisplayCharacter() const {
    return '#';
}

Tile *WallTile::clone() const {
    return new WallTile();
}

Tile *WallTile::changeOnExpended() {
    return this;
}
