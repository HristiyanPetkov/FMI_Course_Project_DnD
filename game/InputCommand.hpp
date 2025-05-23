#ifndef FMI_COURCE_PROJECT_DND_INPUTCOMMAND_HPP
#define FMI_COURCE_PROJECT_DND_INPUTCOMMAND_HPP

#include <iostream>

enum class InputCommand { MOVE_UP, MOVE_LEFT, MOVE_DOWN, MOVE_RIGHT, PRINT_CHARACTER, EXIT };
std::istream& operator>>(std::istream& is, InputCommand& inputCommand);


#endif
