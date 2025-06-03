#ifndef FMI_COURSE_PROJECT_DND_CHARACTERCLASS_HPP
#define FMI_COURSE_PROJECT_DND_CHARACTERCLASS_HPP

#include <iostream>
#include <map>

/**
 * @enum CharacterClass
 * @ingroup Character
 * @brief Enum representing the available character classes.
 */
enum class CharacterClass {
    Human,    ///< Balanced and adaptable class.
    Mage,     ///< Uses magic with high mana.
    Warrior   ///< Strong physical attacker with high strength.
};

/**
 * @brief Overloads the output stream operator for CharacterClass.
 * @param os Output stream.
 * @param characterClass CharacterClass enum value.
 * @return Reference to the output stream.
 */
std::ostream& operator<<(std::ostream& os, const CharacterClass& characterClass);

/**
 * @brief Overloads the input stream operator for CharacterClass.
 * @param is Input stream.
 * @param characterClass CharacterClass enum to read into.
 * @return Reference to the input stream.
 */
std::istream& operator>>(std::istream& is, CharacterClass& characterClass);

#endif
