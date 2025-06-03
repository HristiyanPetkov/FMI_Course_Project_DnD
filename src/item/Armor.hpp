#ifndef FMI_COURSE_PROJECT_DND_ARMOR_HPP
#define FMI_COURSE_PROJECT_DND_ARMOR_HPP

#include "Item.hpp"

/**
 * @class Armor
 * @ingroup Item
 * @brief Represents armor that provides defensive bonuses.
 *
 * Reduces incoming damage when equipped by a character.
 */
class Armor : public Item {
public:
    /**
     * @brief Constructs an armor item.
     * @param name Name of the armor.
     * @param bonus Defensive bonus multiplier.
     */
    Armor(const std::string& name, double bonus);

    /**
     * @brief Virtual destructor.
     */
    ~Armor() override = default;

    /**
     * @brief Clones the armor.
     * @return Pointer to a new Armor object.
     */
    Item *clone() const override;

protected:
    std::string getType() const override;
    double getBonusMultiplier() const override;
};

#endif
