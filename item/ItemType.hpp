#ifndef FMI_COURSE_PROJECT_DND_ITEMTYPE_HPP
#define FMI_COURSE_PROJECT_DND_ITEMTYPE_HPP


#include <iostream>

enum class ItemType { ARMOR, WEAPON, SPELL };
std::ostream& operator<<(std::ostream& os, ItemType type);
std::istream& operator>>(std::istream& is, ItemType& type);


#endif