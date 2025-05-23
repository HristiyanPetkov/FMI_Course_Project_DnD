#include "InputCommand.hpp"

std::istream& operator>>(std::istream& is, InputCommand& inputCommand) {
    std::string input;
    is >> input;
    std::transform(input.begin(), input.end(), input.begin(), [](char c){
        return std::tolower(c);
    });
    if(input == "w") {
        inputCommand = InputCommand::MOVE_UP;
    } else if(input == "a") {
        inputCommand = InputCommand::MOVE_LEFT;
    } else if(input == "s") {
        inputCommand = InputCommand::MOVE_DOWN;
    } else if(input == "d") {
        inputCommand = InputCommand::MOVE_RIGHT;
    } else if(input == "print") {
        inputCommand = InputCommand::PRINT_CHARACTER;
    } else if(input == "exit") {
        inputCommand = InputCommand::EXIT;
    } else {
        throw std::invalid_argument("Invalid command");
    }

    return is;
}