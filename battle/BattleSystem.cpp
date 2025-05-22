#include "BattleSystem.hpp"
#include <ctime>

bool BattleSystem::battle(Character &character, Monster &monster) {
    std::cout << "A battle begins!\n";
    srand(time(nullptr));
    bool playerTurn = (rand() % 2 == 0);

    while (character.isAlive() && monster.isAlive()) {
        std::cout << "Character: " << character.getCurrentHealth() << ", Monster: " << monster.getCurrentHealth() << std::endl;
        if (playerTurn) {
            Character::AttackType type = Character::chooseAttack();
            character.dealDamage(monster, type);
        } else {
            monster.dealDamage(character);
        }
        std::cout << "After: Character: " << character.getCurrentHealth() << ", Monster: " << monster.getCurrentHealth() << std::endl;
        playerTurn = !playerTurn;
    }

    std::cout << "End: Character: " << character.getCurrentHealth() << ", Monster: " << monster.getCurrentHealth() << std::endl;

    if (character.isAlive()) {
        std::cout << "Player wins!\n";
        character.heal();
        return true;
    } else {
        std::cout << "Player died!\n";
        return false;
    }
}
