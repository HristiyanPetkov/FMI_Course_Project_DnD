#ifndef FMI_COURSE_PROJECT_DND_ITEM_HPP
#define FMI_COURSE_PROJECT_DND_ITEM_HPP

#include <iostream>
#include <string>
#include "ItemType.hpp"

class Item {
public:
    Item(const std::string& name, double bonus);
    double applyBonus(double damage) const;
    virtual ~Item() = default;
    virtual Item* clone() const;
    std::ostream& print(std::ostream& os = std::cout) const;
    void serialize(std::ostream &os) const;
    static Item *deserialize(std::istream &is, ItemType type);
protected:
    virtual std::string getType() const;
    virtual double getBonusMultiplier() const;
private:
    std::string name;
    double bonus;
};


#endif
