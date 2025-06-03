#ifndef FMI_COURSE_PROJECT_DND_CHARACTER_HPP
#define FMI_COURSE_PROJECT_DND_CHARACTER_HPP

#include <iostream>
#include <cstddef>
#include <SFML/Graphics.hpp>
#include "CharacterClass.hpp"
#include "../item/Item.hpp"
#include "../item/Weapon.hpp"
#include "../item/ItemType.hpp"

class Monster;

/**
 * @defgroup Character
 * @brief Player character functionalities
 * @details Character class and all associated files for usage of Character objects
 */

/**
 * @class Character
 * @ingroup Character
 * @brief A class representing the player in the game.
 *
 * The Character class encapsulates the core functionalities and attributes
 * of a player character, including health, equipment, stats, combat logic,
 * and serialization for saving and high scores.
 */
class Character {
public:
    /**
     * @brief Types of attacks a character can use.
     */
    enum class AttackType { WEAPON, SPELL };

    /**
     * @brief Default constructor.
     */
    Character();

    /**
     * @brief Constructs a character with a name and class.
     * @param name The character's name.
     * @param characterClass The character's class.
     */
    explicit Character(std::string name, CharacterClass characterClass);

    /**
     * @brief Copy constructor.
     * @param other The character to copy from.
     */
    Character(const Character& other);

    /**
     * @brief Assignment operator.
     * @param other The character to assign from.
     * @return Reference to the assigned character.
     */
    Character& operator=(const Character& other);

    /**
     * @brief Destructor.
     */
    ~Character();

    /**
     * @brief Reduces character's health by the specified damage modified by the armor bonus
     * @param damage The amount of damage to apply.
     */
    void takeDamage(double damage);

    /**
     * @brief Heals character to half health if under, or by 20% if over.
     */
    void heal();

    /**
     * @brief Deals damage to a monster using a specified attack type.
     * @param monster The monster to attack.
     * @param attackType The type of attack used.
     */
    void dealDamage(Monster& monster, AttackType attackType) const;

    /**
     * @brief Checks if the character is alive.
     * @return True if health is greater than zero.
     */
    bool isAlive() const;

    /**
     * @brief Prints the character's stats to the output stream.
     * @note The output is in the form:<br>
     *       name(class)<br>
     *       Strength: , Mana: , Hp:<br>
     *       Equipment:
     * @param os The output stream.
     * @return Reference to the output stream.
     */
    std::ostream& print(std::ostream& os = std::cout) const;

    /**
     * @brief Equips an item of a specified type.
     * @param item Pointer to the item to equip.
     * @param type The type of item (weapon, armor, spell).
     */
    void equipItem(const Item* item, ItemType type);

    /**
     * @brief Gets the current health of the character.
     * @note Used for testing.
     * @return Current health as a double.
     */
    double getCurrentHealth() const;

    /**
     * @brief Prompts the user to choose an attack type.
     * @return The selected AttackType.
     */
    static Character::AttackType chooseAttack();

    /**
     * @brief Levels up the character, increasing stats.
     */
    void levelUp();

    /**
     * @brief Serializes the character data to an output stream.
     * @param os Output stream to write to.
     */
    void serialize(std::ostream &os) const;

    /**
     * @brief Deserializes character data from an input stream.
     * @param is Input stream to read from.
     */
    void deserialize(std::istream &is);

    /**
     * @brief Serializes data needed for high score saving.
     * @param os Output stream.
     */
    void serializeForHighScore(std::ostream &os) const;

    /**
     * @brief Deserializes data from a high score entry.
     * @param is Input stream.
     */
    void deserializeForHighScore(std::istream &is);

    /**
     * @brief Compares two characters based on name lexicographically.
     * @param other The other character.
     * @return True if this character's name is greater.
     */
    bool operator>(const Character& other) const;

    /**
     * @brief Compares two characters based on on name lexicographically.
     * @param other The other character.
     * @return True if this character's name is lesser.
     */
    bool operator<(const Character& other) const;

    /**
     * @brief Displays the character's data using SFML.
     * @param window The SFML render window to draw on.
     */
    void printSFML(sf::RenderWindow &window);

    /**
     * @brief Displays the level-up interface using SFML.
     * @param window The SFML render window.
     */
    void levelUpSFML(sf::RenderWindow &window);

private:
    std::string name;                    ///< Character's name.
    CharacterClass characterClass;       ///< Character's class.
    size_t strength;                     ///< Strength stat.
    size_t mana;                         ///< Mana stat.
    size_t maxHealth;                    ///< Maximum health.
    double currentHealth;                ///< Current health value.
    Item *armor;                         ///< Equipped armor.
    Item *weapon;                        ///< Equipped weapon.
    Item *spell;                         ///< Equipped spell.

    /**
     * @brief Initializes character stats based on class.
     */
    void setInitialStats();

    /**
     * @brief Equips default items for the character.
     */
    void setInitialEquipment();

    /**
     * @brief Copies equipment from another character.
     * @param other The character to copy from.
     */
    void copyEquipment(const Character& other);

    /**
     * @brief Swaps the data with another character.
     * @param character The character to swap with.
     */
    void swap(Character &character);

    /**
     * @brief Increases a specified stat by a number of points.
     * @param stat The stat to increase (e.g., "strength").
     * @param points Number of points to increase.
     */
    void increaseStat(const std::string& stat, unsigned int points);
};

#endif
