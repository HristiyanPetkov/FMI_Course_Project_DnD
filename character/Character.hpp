#ifndef FMI_COURCE_PROJECT_DND_CHARACTER_HPP
#define FMI_COURCE_PROJECT_DND_CHARACTER_HPP


#include <cstddef>
#include "CharacterClass.hpp"
#include "../item/Item.hpp"
#include "../item/Weapon.hpp"
#include <iostream>

class Monster;

class Character {
public:
    enum class AttackType { WEAPON, SPELL };

    Character();
    explicit Character(std::string  name, CharacterClass characterClass);
    Character(const Character& other);
    Character& operator=(const Character& other);
    ~Character();

    void takeDamage(double damage);
    void heal();
    void dealDamage(Monster& monster, AttackType attackType) const;
    bool isAlive() const;
    std::ostream& print(std::ostream& os = std::cout) const;
    void equipItem(const Item* item);
    double getCurrentHealth() const;

    static Character::AttackType chooseAttack();
private:
    std::string name;
    CharacterClass characterClass;
    size_t strength, mana, maxHealth;
    double currentHealth;
    Item *armor;
    Item *weapon;
    Item *spell;

    void setInitialStats();
    void setInitialEquipment();
    void copyEquipment(const Character& other);
    void swap(Character &character);
};


#endif
