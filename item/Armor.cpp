//
// Created by vorte on 5/20/2025.
//

#include "Armor.hpp"

Armor::Armor(const std::string &name, double bonus) : Item(name, bonus) {}

double Armor::getBonusMultiplier() const {
    return 1 - Item::getBonusMultiplier();
}

Item *Armor::clone() {
    return new Armor(*this);
}
