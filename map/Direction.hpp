#ifndef FMI_COURCE_PROJECT_DND_DIRECTION_HPP
#define FMI_COURCE_PROJECT_DND_DIRECTION_HPP

#include <iostream>
#include "../game/InputCommand.hpp"

enum class Direction {UP, RIGHT, DOWN, LEFT};
Direction commandToDirection(InputCommand& command);
std::istream& operator>>(std::istream& is, Direction& direction);


#endif
