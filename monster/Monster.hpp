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
    Monster(const std::string& name, size_t level);
    void takeDamage(double damage);
    void dealDamage(Character& character) const;
    bool isAlive();
    std::ostream& print(std::ostream& os = std::cout) const;
    static double getStartingTakenDamageMult(size_t level);

    double getCurrentHealth() const;
private:
    std::string name;
    size_t strength, mana, maxHealth;
    double currentHealth;
    double takenDamageMult;
};


#endif //FMI_COURCE_PROJECT_DND_MONSTER_HPP
