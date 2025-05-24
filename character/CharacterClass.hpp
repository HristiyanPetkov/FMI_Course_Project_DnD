#ifndef FMI_COURSE_PROJECT_DND_CHARACTERCLASS_HPP
#define FMI_COURSE_PROJECT_DND_CHARACTERCLASS_HPP

#include <iostream>
#include <map>

enum class CharacterClass {
    Human, Mage, Warrior
};

std::ostream& operator<<(std::ostream& os, const CharacterClass& characterClass);
std::istream& operator>>(std::istream& is, CharacterClass& characterClass);

#endif
