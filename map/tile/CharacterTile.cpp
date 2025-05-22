#include "CharacterTile.hpp"

void CharacterTile::apply(Character &otherCharacter) {
    otherCharacter.print();
}

char CharacterTile::getDisplayCharacter() const {
    return 'C';
}

Tile *CharacterTile::clone() const {
    return new CharacterTile(*this);
}
