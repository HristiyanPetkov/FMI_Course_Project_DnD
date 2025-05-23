#include "Character.hpp"

#include <utility>
#include <cstring>
#include "../item/Armor.hpp"
#include "../item/Weapon.hpp"
#include "../item/Spell.hpp"
#include "../monster/Monster.hpp"

Character::Character()
: name(), characterClass(CharacterClass::Human), strength(0), mana(0), maxHealth(0), currentHealth(0),
  armor(nullptr), weapon(nullptr), spell(nullptr) {}

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
            strength = 45;
            mana = 30;
            maxHealth = 80;
            currentHealth = 80;
            break;
        case CharacterClass::Mage:
            strength = 25;
            mana = 70;
            maxHealth = 100;
            currentHealth = 100;
            break;
        case CharacterClass::Warrior:
            strength = 60;
            mana = 25;
            maxHealth = 120;
            currentHealth = 120;
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

std::ostream &Character::print(std::ostream &os) const {
    os << name << "(" << characterClass << ")" << std::endl;
    os << "Strength: " << strength << ", Mana: " << mana << ", Health: " << currentHealth << "\\" << maxHealth << std::endl;
    os << "Equipment: " << std::endl;
    armor->print(os);
    weapon->print(os);
    return spell->print(os);
}

void Character::dealDamage(Monster &monster, Character::AttackType attackType) const {
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

void Character::equipItem(const Item *item, ItemType itemType) {
    if (!item) return;

    switch(itemType) {
        case ItemType::ARMOR:
            delete armor;
            armor = item->clone();
            break;
        case ItemType::WEAPON:
            delete weapon;
            weapon = item->clone();
            break;
        case ItemType::SPELL:
            delete spell;
            spell = item->clone();
            break;
    }
}

double Character::getCurrentHealth() const {
    return currentHealth;
}

Character::AttackType Character::chooseAttack() {
    while(true) {
        std::cout << "Attack type: 1.Weapon, 2.Spell" << std::endl;
        std::string choice;
        std::cin >> choice;
        if(choice == "1" || choice == "Weapon") {
            return Character::AttackType::WEAPON;
        } else if(choice == "2" || choice == "Spell") {
            return Character::AttackType::SPELL;
        } else {
            std::cout << "Invalid attack type" << std::endl;
        }
    }
}
