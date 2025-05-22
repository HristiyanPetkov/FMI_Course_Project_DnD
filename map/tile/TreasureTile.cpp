#include "TreasureTile.hpp"

TreasureTile::TreasureTile(Item *item)
: item(item->clone()) {}

TreasureTile::TreasureTile(const Item& item)
: item(item.clone()) {}

TreasureTile::TreasureTile(const TreasureTile &other)
: item(other.item->clone()) {}

TreasureTile &TreasureTile::operator=(const TreasureTile &other) {
    TreasureTile copy(other);
    std::swap(item, copy.item);

    return *this;
}

void TreasureTile::apply(Character &character) {
    character.equipItem(item);
}

char TreasureTile::getDisplayCharacter() const {
    return 'T';
}

Tile *TreasureTile::clone() const {
    return new TreasureTile(*this);
}

TreasureTile::~TreasureTile() {
    delete item;
}

Tile *TreasureTile::generateRandomTreasureTile(unsigned int level) {
    return new TreasureTile(Weapon("Sword", 10));
}
