#include "ItemType.hpp"

std::ostream& operator<<(std::ostream& os, ItemType type) {
    switch (type) {
        case ItemType::ARMOR:
            return os << "Armor";
        case ItemType::WEAPON:
            return os << "Weapon";
        case ItemType::SPELL:
            return os << "Spell";
    }
    throw std::invalid_argument("Invalid type");
}

std::istream& operator>>(std::istream& is, ItemType& type) {
    std::string typeInString;
    is >> typeInString;
    if(typeInString == "Armor") {
        type = ItemType::ARMOR;
    } else if(typeInString == "Weapon") {
        type = ItemType::WEAPON;
    } else if(typeInString == "Spell") {
        type = ItemType::SPELL;
    }
    return is;
}