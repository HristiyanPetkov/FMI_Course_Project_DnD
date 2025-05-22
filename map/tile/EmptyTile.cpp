#include "EmptyTile.hpp"

void EmptyTile::apply(Character &character) {}

char EmptyTile::getDisplayCharacter() const {
    return '.';
}

Tile *EmptyTile::clone() const {
    return new EmptyTile();
}

bool EmptyTile::isEmpty() {
    return true;
}
