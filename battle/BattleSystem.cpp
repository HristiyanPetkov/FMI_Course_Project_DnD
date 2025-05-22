#include "BattleSystem.hpp"

bool BattleSystem::battle(Character &character, Monster &monster) {
    std::cout << "A battle begins!\n";
    bool playerTurn = (rand() % 2 == 0);

    while (character.isAlive() && monster.isAlive()) {
        if (playerTurn) {
            Character::AttackType type = Character::chooseAttack();
            character.dealDamage(monster, type);
        } else {
            monster.dealDamage(character);
        }
        playerTurn = !playerTurn;
    }

    if (character.isAlive()) {
        std::cout << "Player wins!\n";
        character.heal();
        return true;
    } else {
        std::cout << "Player died!\n";
        return false;
    }
}
