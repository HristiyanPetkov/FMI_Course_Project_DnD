#ifndef FMI_COURSE_PROJECT_DND_ITEM_HPP
#define FMI_COURSE_PROJECT_DND_ITEM_HPP

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "ItemType.hpp"

/**
 * @defgroup Item
 * @brief All supported items
 * @details Abstract class Item and all supported subtypes of items
 */

/**
 * @class Item
 * @ingroup Item
 * @brief Abstract base class for all in-game items.
 *
 * Items provide stat bonuses and can be equipped by characters.
 */
class Item {
public:
    /**
     * @brief Constructs an item with a name and bonus value.
     * @param name The item's name.
     * @param bonus The bonus multiplier it provides.
     */
    Item(const std::string& name, double bonus);

    /**
     * @brief Applies the item's bonus to a given damage value.
     * @param damage Base damage.
     * @return Modified damage after applying bonus.
     */
    double applyBonus(double damage) const;

    /**
     * @brief Virtual destructor.
     */
    virtual ~Item() = default;

    /**
     * @brief Clones the item (used for polymorphism).
     * @return A new copy of the item.
     */
    virtual Item* clone() const;

    /**
     * @brief Prints item information to an output stream.
     * @note The output is in the form:<br>
     *       ItemType: name bonus
     * @param os Output stream.
     * @return Reference to the output stream.
     */
    std::ostream& print(std::ostream& os = std::cout) const;

    /**
     * @brief Serializes the item to a stream.
     * @param os Output stream.
     */
    void serialize(std::ostream &os) const;

    /**
     * @brief Deserializes an item from a stream.
     * @param is Input stream.
     * @param type Type of the item.
     * @return Pointer to a newly created item.
     */
    static Item *deserialize(std::istream &is, ItemType type);

    /**
     * @brief Draws the item in an SFML window.
     * @param window SFML window.
     */
    void printSFML(sf::RenderWindow &window);

protected:
    /**
     * @brief Returns the item's type as a string.
     * @note Used for console outputs.
     * @return Item type string.
     */
    virtual std::string getType() const;

    /**
     * @brief Gets the bonus multiplier for the item.
     * @return Bonus multiplier.
     */
    virtual double getBonusMultiplier() const;

private:
    std::string name; ///< Name of the item.
    double bonus;     ///< Bonus multiplier.
};

#endif
