#ifndef FMI_COURSE_PROJECT_DND_DIRECTION_HPP
#define FMI_COURSE_PROJECT_DND_DIRECTION_HPP

#include <iostream>
#include "../game/InputCommand.hpp"

/**
 * @enum Direction
 * @ingroup Map
 * @brief Represents directional movement.
 */
enum class Direction {
    UP,     ///< Move up
    RIGHT,  ///< Move right
    DOWN,   ///< Move down
    LEFT    ///< Move left
};

/**
 * @brief Converts an input command to a direction.
 * @param command The input command.
 * @return Corresponding direction.
 */
Direction commandToDirection(InputCommand& command);

/**
 * @brief Overloads input operator for Direction.
 * @param is Input stream.
 * @param direction Direction variable to modify.
 * @return Input stream reference.
 */
std::istream& operator>>(std::istream& is, Direction& direction);

#endif
