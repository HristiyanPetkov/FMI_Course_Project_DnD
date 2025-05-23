#ifndef FMI_COURCE_PROJECT_DND_ITEM_HPP
#define FMI_COURCE_PROJECT_DND_ITEM_HPP

#include <iostream>
#include <string>

enum class ItemType { ARMOR, WEAPON, SPELL };

class Item {
public:
    Item(const std::string& name, double bonus);
    double applyBonus(double damage) const;
    virtual ~Item() = default;
    virtual Item* clone() const;
    std::ostream& print(std::ostream& os = std::cout) const;
protected:
    virtual std::string getType() const;
    virtual double getBonusMultiplier() const;
private:
    std::string name;
    double bonus;
};


#endif
