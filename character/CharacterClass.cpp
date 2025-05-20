#include "CharacterClass.hpp"

std::ostream& operator<<(std::ostream& os, CharacterClass characterClass) {
    switch(characterClass) {
        case CharacterClass::Human:
            return os << "Human";
            // break; // Unnecessary after a return statement
        case CharacterClass::Mage:
            return os << "Mage";
            // break; // Unnecessary after a return statement
        case CharacterClass::Warrior:
            return os << "Warrior";
            // break; // Unnecessary after a return statement
        default:
            // It's good practice to throw an exception for unhandled enum values.
            // Ensure you #include <stdexcept>
            throw std::invalid_argument("Unsupported CharacterClass value for streaming.");
    }
}