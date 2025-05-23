#include "Monster.hpp"
#include "../character/Character.hpp"
#include <ctime>
#include <iomanip>

Monster::Monster()
: name(), strength(0), mana(0), maxHealth(0), currentHealth(0), takenDamageMult(0) {}

Monster::Monster(const std::string &name, unsigned int level)
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

double Monster::getStartingTakenDamageMult(unsigned int level) {
    double result = 15;
    for(size_t i = 0; i < level - 1; ++i) {
        result += result * 0.05;
    }

    return std::max(1.0, 100 - result) / 100;
}

bool Monster::isAlive() const {
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

void Monster::serialize(std::ostream &os) {
    os << std::quoted(name) << " " << strength << " " << mana << " " << maxHealth << " " << currentHealth << " " << takenDamageMult << std::endl;
}

void Monster::deserialize(std::istream &is) {
    is >> std::quoted(name) >> strength >> mana >> maxHealth >> currentHealth >> takenDamageMult;
}
