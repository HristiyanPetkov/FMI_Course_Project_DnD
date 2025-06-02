#ifndef FMI_COURSE_PROJECT_DND_INPUTCOMMAND_HPP
#define FMI_COURSE_PROJECT_DND_INPUTCOMMAND_HPP

#include <iostream>

/**
 * @enum InputCommand
 * @ingroup Game
 * @brief Represents valid input commands from the player.
 */
enum class InputCommand {
    MOVE_UP,           ///< Move character up.
    MOVE_LEFT,         ///< Move character left.
    MOVE_DOWN,         ///< Move character down.
    MOVE_RIGHT,        ///< Move character right.
    PRINT_CHARACTER,   ///< Print character details.
    EXIT,              ///< Exit the game.
    NONE               ///< No input or invalid input.
};

/**
 * @brief Parses an InputCommand from input stream.
 * @param is Input stream.
 * @param inputCommand Command to parse into.
 * @return Reference to input stream.
 */
std::istream& operator>>(std::istream& is, InputCommand& inputCommand);

#endif
