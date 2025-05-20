//
// Created by vorte on 5/20/2025.
//

#ifndef FMI_COURCE_PROJECT_DND_SPELL_HPP
#define FMI_COURCE_PROJECT_DND_SPELL_HPP


#include "Item.hpp"

class Spell : public Item {
public:
    Spell(const std::string& name, double bonus);
    ~Spell() override = default;
    Item *clone() const override;
    std::string getType() const override;
protected:
    double getBonusMultiplier() const override;
};


#endif //FMI_COURCE_PROJECT_DND_SPELL_HPP
