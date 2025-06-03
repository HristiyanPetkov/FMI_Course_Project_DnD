#ifndef FMI_COURSE_PROJECT_DND_SPELL_HPP
#define FMI_COURSE_PROJECT_DND_SPELL_HPP

#include "Item.hpp"

/**
 * @class Spell
 * @ingroup Item
 * @brief Represents a magical item.
 *
 * Spells enhance magical attacks.
 */
class Spell : public Item {
public:
    /**
     * @brief Constructs a spell with a name and bonus.
     * @param name Name of the spell.
     * @param bonus Bonus multiplier.
     */
    Spell(const std::string& name, double bonus);

    /**
     * @brief Virtual destructor.
     */
    ~Spell() override = default;

    /**
     * @brief Clones the spell item.
     * @return Pointer to a new Spell object.
     */
    Item *clone() const override;

protected:
    std::string getType() const override;
    double getBonusMultiplier() const override;
};

#endif
