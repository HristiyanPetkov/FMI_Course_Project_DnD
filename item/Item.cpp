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

std::ostream &Item::print(std::ostream &os) const {
    return os << getType() << ": " << name << " " << bonus << std::endl;
}

std::string Item::getType() const {
    return "Common Item";
}
