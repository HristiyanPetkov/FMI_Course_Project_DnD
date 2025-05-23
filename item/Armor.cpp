#include "Armor.hpp"

Armor::Armor(const std::string &name, double bonus) : Item(name, bonus) {}

double Armor::getBonusMultiplier() const {
    return 1 - Item::getBonusMultiplier();
}

Item *Armor::clone() const {
    return new Armor(*this);
}

std::string Armor::getType() const {
    return "Armor";
}
