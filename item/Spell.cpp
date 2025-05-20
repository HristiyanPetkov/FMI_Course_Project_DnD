//
// Created by vorte on 5/20/2025.
//

#include "Spell.hpp"

Spell::Spell(const std::string &name, double bonus) : Item(name, bonus) {}

double Spell::getBonusMultiplier() const {
    return 1 + Item::getBonusMultiplier();
}

Item *Spell::clone() {
    return new Spell(*this);
}
