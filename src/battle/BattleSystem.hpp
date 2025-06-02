#ifndef FMI_COURSE_PROJECT_DND_BATTLESYSTEM_HPP
#define FMI_COURSE_PROJECT_DND_BATTLESYSTEM_HPP

#include "../character/Character.hpp"
#include "../monster/Monster.hpp"

/**
 * @class BattleSystem
 * @brief Handles battles between characters and monsters.
 * @see Character, Monster
 *
 * Provides methods for conducting turn-based combat, both in
 * console and with SFML graphical output.
 */
class BattleSystem {
public:
    /**
     * @brief Executes a battle between a character and a monster in console.
     * @param character The player character.
     * @param monster The monster to fight.
     * @return True if the character wins, false if defeated.
     */
    static bool battle(Character& character, Monster& monster);

    /**
     * @brief Executes a battle using SFML rendering.
     * @param character The player character.
     * @param monster The monster to fight.
     * @param window The SFML window to render the battle in.
     * @return True if the character wins, false otherwise.
     */
    static bool battle(Character& character, Monster& monster, sf::RenderWindow& window);
};

#endif
