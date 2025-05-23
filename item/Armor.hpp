#ifndef FMI_COURCE_PROJECT_DND_ARMOR_HPP
#define FMI_COURCE_PROJECT_DND_ARMOR_HPP


#include "Item.hpp"

class Armor : public Item {
public:
    Armor(const std::string& name, double bonus);
    ~Armor() override = default;
    Item *clone() const override;
protected:
    std::string getType() const override;
    double getBonusMultiplier() const override;
};


#endif
