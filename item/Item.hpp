//
// Created by vorte on 5/20/2025.
//

#ifndef FMI_COURCE_PROJECT_DND_ITEM_HPP
#define FMI_COURCE_PROJECT_DND_ITEM_HPP

#include <iostream>
#include <string>

class Item {
public:
    Item(const std::string& name, double bonus);
    double applyBonus(double damage) const;
    virtual ~Item() = default;
    virtual Item* clone();
    std::ostream& print(std::ostream& os);
protected:
    virtual double getBonusMultiplier() const;
private:
    std::string name;
    double bonus;
};


#endif //FMI_COURCE_PROJECT_DND_ITEM_HPP
