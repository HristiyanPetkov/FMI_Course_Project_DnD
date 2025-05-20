#include <iostream>
#include "character/Character.hpp"

int main() {
    Character hero("Pesho", CharacterClass::Warrior);
    hero.print();
    hero.takeDamage(10);
    hero.print();
    return 0;
}
