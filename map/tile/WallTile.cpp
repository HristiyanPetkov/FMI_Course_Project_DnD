#include "WallTile.hpp"

char WallTile::getDisplayCharacter() const {
    return '#';
}

Tile *WallTile::clone() const {
    return new WallTile();
}

Tile *WallTile::changeOnExpended() {
    return this;
}

sf::Color WallTile::getColor() {
    return sf::Color::White;
}
