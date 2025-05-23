#include "Direction.hpp"

Direction commandToDirection(InputCommand& command) {
    switch(command) {
        case InputCommand::MOVE_UP:
            return Direction::UP;
        case InputCommand::MOVE_LEFT:
            return Direction::LEFT;
        case InputCommand::MOVE_DOWN:
            return Direction::DOWN;
        case InputCommand::MOVE_RIGHT:
            return Direction::RIGHT;
        default:
            throw std::invalid_argument("Invalid conversion: command is not a move command");
    }
}

std::istream& operator>>(std::istream& is, Direction& direction) {
    char input;
    is >> input;

    switch(_tolower(input)) {
        case 'w':
            direction = Direction::UP;
            break;
        case 'a':
            direction = Direction::LEFT;
            break;
        case 's':
            direction = Direction::DOWN;
            break;
        case 'd':
            direction = Direction::RIGHT;
            break;
        default:
            throw std::invalid_argument("Invalid Direction");
    }

    return is;
}