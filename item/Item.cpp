//
// Created by vorte on 5/20/2025.
//

#include "Item.hpp"

Item::Item(const std::string& name, double bonus)
: name(name), bonus(bonus){}

double Item::applyBonus(double damage) const {
    return damage * getBonusMultiplier();
}

double Item::getBonusMultiplier() const {
    return bonus / 100;
}

Item *Item::clone() const {
    return new Item(*this);
}

std::ostream &Item::print(std::ostream &os) {
    return os << name << " " << bonus << std::endl;
}

std::string Item::getType() const {
    return "Common Item";
}
