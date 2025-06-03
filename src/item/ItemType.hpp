#ifndef FMI_COURSE_PROJECT_DND_ITEMTYPE_HPP
#define FMI_COURSE_PROJECT_DND_ITEMTYPE_HPP

#include <iostream>

/**
 * @enum ItemType
 * @ingroup Item
 * @brief Types of equipable items.
 */
enum class ItemType {
    ARMOR,  ///< Defensive item that reduces damage taken.
    WEAPON, ///< Offensive item that increases damage dealt.
    SPELL   ///< Magical item affecting magic abilities.
};

/**
 * @brief Overloads the output stream for ItemType.
 * @param os Output stream.
 * @param type ItemType to output.
 * @return Reference to output stream.
 */
std::ostream& operator<<(std::ostream& os, ItemType type);

/**
 * @brief Overloads the input stream for ItemType.
 * @param is Input stream.
 * @param type ItemType to set.
 * @return Reference to input stream.
 */
std::istream& operator>>(std::istream& is, ItemType& type);

#endif
