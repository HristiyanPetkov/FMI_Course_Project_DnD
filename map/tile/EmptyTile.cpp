#include "EmptyTile.hpp"

char EmptyTile::getDisplayCharacter() const {
    return '.';
}

Tile *EmptyTile::clone() const {
    return new EmptyTile();
}

bool EmptyTile::isEmpty() {
    return true;
}

sf::Color EmptyTile::getColor() {
    return sf::Color::Black;
}
