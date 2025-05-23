#ifndef FMI_COURCE_PROJECT_DND_SPELL_HPP
#define FMI_COURCE_PROJECT_DND_SPELL_HPP


#include "Item.hpp"

class Spell : public Item {
public:
    Spell(const std::string& name, double bonus);
    ~Spell() override = default;
    Item *clone() const override;
protected:
    std::string getType() const override;
    double getBonusMultiplier() const override;
};


#endif
