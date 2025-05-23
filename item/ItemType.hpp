//
// Created by vorte on 5/23/2025.
//

#ifndef FMI_COURCE_PROJECT_DND_ITEMTYPE_HPP
#define FMI_COURCE_PROJECT_DND_ITEMTYPE_HPP


#include <iostream>

enum class ItemType { ARMOR, WEAPON, SPELL };
std::ostream& operator<<(std::ostream& os, ItemType type);
std::istream& operator>>(std::istream& is, ItemType& type);


#endif //FMI_COURCE_PROJECT_DND_ITEMTYPE_HPP
