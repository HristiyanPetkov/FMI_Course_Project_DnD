#ifndef FMI_COURSE_PROJECT_DND_WEAPON_HPP
#define FMI_COURSE_PROJECT_DND_WEAPON_HPP

#include "Item.hpp"

/**
 * @class Weapon
 * @ingroup Item
 * @brief Represents a weapon item.
 *
 * Weapons enhance the damage dealt by characters.
 */
class Weapon : public Item {
public:
    /**
     * @brief Constructs a weapon with name and bonus.
     * @param name Weapon name.
     * @param bonus Bonus multiplier.
     */
    Weapon(const std::string& name, double bonus);

    /**
     * @brief Virtual destructor.
     */
    ~Weapon() override = default;

    /**
     * @brief Clones the weapon.
     * @return Pointer to a new Weapon object.
     */
    Item *clone() const override;

protected:
    std::string getType() const override;
    double getBonusMultiplier() const override;
};

#endif
