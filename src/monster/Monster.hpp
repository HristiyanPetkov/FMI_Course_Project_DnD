#ifndef FMI_COURSE_PROJECT_DND_MONSTER_HPP
#define FMI_COURSE_PROJECT_DND_MONSTER_HPP

#include <iostream>
#include <string>
#include <cstddef>
#include <SFML/Graphics.hpp>

class Character;

/**
 * @class Monster
 * @brief Represents an enemy in the game that the player can fight.
 *
 * Monsters have stats like health, strength, and damage multipliers,
 * and can interact with characters in combat.
 */
class Monster {
public:
    /**
     * @brief Default constructor.
     */
    Monster();

    /**
     * @brief Constructs a monster with a name and level.
     * @param name Monster's name.
     * @param level Monster's level, affecting stats.
     */
    Monster(const std::string& name, unsigned level);

    /**
     * @brief Applies damage to the monster.
     * @param damage Amount of damage to apply.
     */
    void takeDamage(double damage);

    /**
     * @brief Deals damage to a Character.
     * @param character The Character to attack.
     */
    void dealDamage(Character& character) const;

    /**
     * @brief Checks if the monster is still alive.
     * @return True if current health > 0.
     */
    bool isAlive() const;

    /**
     * @brief Prints the monster's details to an output stream.
     * @note The output is in the form:<br>
     *       name<br>
     *       Strength: , Mana: , Health:<br>
     *       Damage reduction mult:
     * @param os The output stream.
     * @return Reference to the output stream.
     */
    std::ostream& print(std::ostream& os = std::cout) const;

    /**
     * @brief Returns the current health of the monster.
     * @note Used for testing.
     * @return Current health as a double.
     */
    double getCurrentHealth() const;

    /**
     * @brief Calculates initial damage reduction multiplier based on level.
     * @param level The monster's level.
     * @return Damage reduction multiplier.
     */
    static double getStartingTakenDamageMult(unsigned level);

    /**
     * @brief Serializes the monster's data to a stream.
     * @param os Output stream.
     */
    void serialize(std::ostream &os) const;

    /**
     * @brief Deserializes monster data from a stream.
     * @param is Input stream.
     */
    void deserialize(std::istream &is);

    /**
     * @brief Displays the monster's data using SFML.
     * @param window The SFML render window to draw on.
     */
    void printSFML(sf::RenderWindow &window);

private:
    std::string name;         ///< Name of the monster.
    size_t strength;          ///< Strength stat.
    size_t mana;              ///< Mana stat.
    size_t maxHealth;         ///< Maximum health.
    double currentHealth;     ///< Current health value.
    double takenDamageMult;   ///< Damage multiplier based on level.
};

#endif
