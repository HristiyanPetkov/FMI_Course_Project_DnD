//
// Created by vorte on 5/20/2025.
//

#include "Weapon.hpp"

Weapon::Weapon(const std::string &name, double bonus) : Item(name, bonus) {}

double Weapon::getBonusMultiplier() const {
    return 1 + Item::getBonusMultiplier();
}

Item *Weapon::clone() const {
    return new Weapon(*this);
}

std::string Weapon::getType() const {
    return "Weapon";
}
