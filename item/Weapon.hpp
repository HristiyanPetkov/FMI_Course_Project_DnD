#ifndef FMI_COURSE_PROJECT_DND_WEAPON_HPP
#define FMI_COURSE_PROJECT_DND_WEAPON_HPP


#include "Item.hpp"

class Weapon : public Item {
public:
    Weapon(const std::string& name, double bonus);
    ~Weapon() override = default;
    Item *clone() const override;
protected:
    std::string getType() const override;
    double getBonusMultiplier() const override;
};


#endif
