#include "Monster.hpp"
#include "../character/Character.hpp"
#include <ctime>

Monster::Monster(const std::string &name, size_t level)
: name(name), strength(25 + 10 * (level-1)), mana(25 + 10 * (level - 1)), maxHealth(50 + 10 * (level - 1)),
  currentHealth(static_cast<double>(maxHealth)), takenDamageMult(Monster::getStartingTakenDamageMult(level))
{}

void Monster::takeDamage(double damage) {
    currentHealth = std::max(0.0, currentHealth - damage * takenDamageMult);
}

void Monster::dealDamage(Character &character) const {
    srand( (unsigned)time(nullptr) );
    int randomNumber = rand() % 2;
    switch(randomNumber) {
        case 0:
            character.takeDamage(strength);
            break;
        case 1:
            character.takeDamage(mana);
            break;
    }
}

double Monster::getStartingTakenDamageMult(size_t level) {
    double result = 15;
    for(size_t i = 0; i < level - 1; ++i) {
        result += result * 0.05;
    }

    return std::max(1.0, 100 - result) / 100;
}

bool Monster::isAlive() {
    return currentHealth != 0;
}

std::ostream &Monster::print(std::ostream &os) const {
    os << name << std::endl;
    os << "Strength: " << strength << ", Mana: " << mana << ", Health: " << currentHealth << "\\" << maxHealth << std::endl;
    return os << "Damage reduction mult: " << takenDamageMult << std::endl;
}

double Monster::getCurrentHealth() const {
    return currentHealth;
}
