#include "Spell.hpp"

Spell::Spell(const std::string &name, double bonus) : Item(name, bonus) {}

double Spell::getBonusMultiplier() const {
    return 1 + Item::getBonusMultiplier();
}

Item *Spell::clone() const {
    return new Spell(*this);
}

std::string Spell::getType() const {
    return "Spell";
}
