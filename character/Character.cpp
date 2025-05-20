//
// Created by vorte on 5/20/2025.
//

#include "Character.hpp"

#include <utility>
#include <cstring>
#include "../item/Armor.hpp"
#include "../item/Weapon.hpp"
#include "../item/Spell.hpp"
#include "../monster/Monster.hpp"

Character::Character(std::string  name, CharacterClass characterClass)
: name(std::move(name)), characterClass(characterClass), strength(0), mana(0), maxHealth(0), currentHealth(0),
  armor(nullptr), weapon(nullptr), spell(nullptr)
{
    setInitialStats();
    setInitialEquipment();
}

void Character::setInitialStats() {
    switch(characterClass) {
        case CharacterClass::Human:
            strength = 30;
            mana = 20;
            maxHealth = 50;
            currentHealth = 50;
            break;
        case CharacterClass::Mage:
            strength = 10;
            mana = 40;
            maxHealth = 50;
            currentHealth = 50;
            break;
        case CharacterClass::Warrior:
            strength = 40;
            mana = 10;
            maxHealth = 50;
            currentHealth = 50;
            break;
        default:
            throw std::invalid_argument("Character class is not defined");
    }
}

void Character::setInitialEquipment() {
    armor = new Armor("Clothes", 0);
    weapon = new Weapon("Basic sword", 20);
    spell = new Spell("Fireball", 20);
}

Character::Character(const Character &other)
: name(other.name),
  characterClass(other.characterClass),
  strength(other.strength),
  mana(other.mana),
  maxHealth(other.maxHealth),
  currentHealth(other.currentHealth),
  armor(nullptr),
  weapon(nullptr),
  spell(nullptr)
{
    copyEquipment(other);
}

Character &Character::operator=(const Character &other) {
    Character copy(other);
    swap(copy);

    return *this;
}

Character::~Character() {
    delete armor;
    delete weapon;
    delete spell;
}

void Character::takeDamage(double damage) {
    currentHealth = std::max(0.0, currentHealth - armor->applyBonus(damage));
}

void Character::heal() {
    if(currentHealth > maxHealth * 0.5) {
        currentHealth = std::min(currentHealth + 0.2 * maxHealth, static_cast<double>(maxHealth));
    } else {
        currentHealth = 0.5 * maxHealth;
    }
}

void Character::copyEquipment(const Character& other) {
    if(other.armor != nullptr) {
        armor = other.armor->clone();
    }
    if(other.weapon != nullptr) {
        weapon = other.weapon->clone();
    }
    if(other.spell != nullptr) {
        spell = other.spell->clone();
    }
}

void Character::swap(Character &other) {
    using std::swap;
    swap(name, other.name);
    swap(characterClass, other.characterClass);
    swap(strength, other.strength);
    swap(mana, other.mana);
    swap(maxHealth, other.maxHealth);
    swap(currentHealth, other.currentHealth);
    swap(armor, other.armor);
    swap(weapon, other.weapon);
    swap(spell, other.spell);
}

std::ostream &Character::print(std::ostream &os) {
    os << name << "(" << characterClass << ")" << std::endl;
    os << "Strength: " << strength << ", Mana: " << mana << ", Health: " << currentHealth << "\\" << maxHealth << std::endl;
    os << "Equipment: " << std::endl;
    armor->print(os);
    weapon->print(os);
    return spell->print(os);
}

void Character::dealDamage(Monster &monster, Character::AttackType attackType) {
    switch(attackType) {
        case AttackType::WEAPON:
            monster.takeDamage(weapon->applyBonus(static_cast<double>(strength)));
            break;
        case AttackType::SPELL:
            monster.takeDamage(spell->applyBonus(static_cast<double>(mana)));
            break;
    }
}

bool Character::isAlive() const {
    return currentHealth != 0;
}

void Character::equipItem(const Item *item) {
    if (!item) return;

    std::string type = item->getType();
    if(std::strcmp("Armor", type.c_str()) == 0) {
        delete armor;
        armor = item->clone();
    } else if(std::strcmp("Weapon", type.c_str()) == 0) {
        delete weapon;
        weapon = item->clone();
    } else if(std::strcmp("Spell", type.c_str()) == 0) {
        delete spell;
        spell = item->clone();
    } else {
        throw std::invalid_argument("Invalid item type");
    }
}

double Character::getCurrentHealth() const {
    return currentHealth;
}
