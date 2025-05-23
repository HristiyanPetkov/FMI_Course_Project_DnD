//
// Created by vorte on 5/20/2025.
//

#ifndef FMI_COURCE_PROJECT_DND_MONSTER_HPP
#define FMI_COURCE_PROJECT_DND_MONSTER_HPP

#include <iostream>
#include <string>
#include <cstddef>

class Character;

class Monster {
public:
    Monster();
    Monster(const std::string& name, unsigned level);
    void takeDamage(double damage);
    void dealDamage(Character& character) const;
    bool isAlive() const;
    std::ostream& print(std::ostream& os = std::cout) const;
    double getCurrentHealth() const;

    static double getStartingTakenDamageMult(unsigned level);

    void serialize(std::ostream &os);

    void deserialize(std::istream &is);

private:
    std::string name;
    size_t strength, mana, maxHealth;
    double currentHealth;
    double takenDamageMult;
};


#endif //FMI_COURCE_PROJECT_DND_MONSTER_HPP
