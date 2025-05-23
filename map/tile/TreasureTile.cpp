#include "TreasureTile.hpp"
#include "EmptyTile.hpp"
#include "../../item/Armor.hpp"
#include "../../item/Spell.hpp"

TreasureTile::TreasureTile(Item *item, ItemType type)
: item(item->clone()), type(type) {}

TreasureTile::TreasureTile(const Item& item, ItemType type)
: item(item.clone()), type(type) {}

TreasureTile::TreasureTile(const TreasureTile &other)
: item(other.item->clone()), type(other.type) {}

TreasureTile &TreasureTile::operator=(const TreasureTile &other) {
    TreasureTile copy(other);
    std::swap(item, copy.item);
    std::swap(type, copy.type);

    return *this;
}

void TreasureTile::apply(Character &character) {
    item->print();
    std::cout << "Eqip item? ";
    char choice;
    std::cin >> choice;
    if(std::tolower(choice) == 'y') {
        character.equipItem(item, type);
    }
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
    srand(time(nullptr));
    ItemType genType = static_cast<ItemType>(rand() % 3);

    switch(genType) {
        case ItemType::ARMOR:
            return new TreasureTile(Armor("Armor", getBonusFromLevel(level)), ItemType::ARMOR);
        case ItemType::WEAPON:
            return new TreasureTile(Weapon("Sword", getBonusFromLevel(level)), ItemType::WEAPON);
        case ItemType::SPELL:
            return new TreasureTile(Spell("Spell", getBonusFromLevel(level)), ItemType::SPELL);
        default:
            throw std::invalid_argument("Invalid item Type");
    }
}

double TreasureTile::getBonusFromLevel(unsigned int level) {
    double bonus = 20;
    for(size_t i = 1; i < level; ++i) {
        bonus *= 1.1;
    }
    return bonus;
}

Tile *TreasureTile::changeOnExpended() {
    delete this;
    return new EmptyTile();
}

void TreasureTile::serialize(std::ostream &os) {
    os << getDisplayCharacter() << " " << type << " ";
    item->serialize(os);
}
