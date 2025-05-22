#include "Tile.hpp"
#include "EmptyTile.hpp"

bool Tile::isEmpty() {
    return false;
}

Tile *Tile::changeOnExpended() {
    return this;
}
