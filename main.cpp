#include <iostream>
#include "character/Character.hpp"
#include "item/Armor.hpp"
#include "item/Weapon.hpp"
#include "item/Spell.hpp"

int main() {
    Character character("Hero", CharacterClass::Human);
    Item* armor = new Armor("Leather Armor", 50);
    Item* weapon = new Weapon("Steel Sword", 50);
    Item* spell = new Spell("Ice Spear", 50);
    character.equipItem(spell);
    character.equipItem(weapon);
    character.equipItem(armor);
    character.takeDamage(20);

    character.print();

    delete armor;
    delete weapon;
    delete spell;

    return 0;
}
