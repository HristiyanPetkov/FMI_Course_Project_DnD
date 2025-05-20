//
// Created by vorte on 5/20/2025.
//

#ifndef FMI_COURCE_PROJECT_DND_WEAPON_HPP
#define FMI_COURCE_PROJECT_DND_WEAPON_HPP


#include "Item.hpp"

class Weapon : public Item {
public:
    Weapon(const std::string& name, double bonus);
    ~Weapon() override = default;
    Item *clone() const override;
    std::string getType() const override;
protected:
    double getBonusMultiplier() const override;
};


#endif //FMI_COURCE_PROJECT_DND_WEAPON_HPP
