//
// Created by vorte on 5/20/2025.
//

#ifndef FMI_COURCE_PROJECT_DND_ARMOR_HPP
#define FMI_COURCE_PROJECT_DND_ARMOR_HPP


#include "Item.hpp"

class Armor : public Item {
public:
    Armor(const std::string& name, double bonus);
    ~Armor() override = default;
    Item *clone() override;
protected:
    double getBonusMultiplier() const override;
};


#endif //FMI_COURCE_PROJECT_DND_ARMOR_HPP
