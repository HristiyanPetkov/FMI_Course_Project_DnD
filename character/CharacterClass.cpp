#include "CharacterClass.hpp"

std::ostream& operator<<(std::ostream& os, const CharacterClass& characterClass) {
    switch(characterClass) {
        case CharacterClass::Human:
            return os << "Human";
        case CharacterClass::Mage:
            return os << "Mage";
        case CharacterClass::Warrior:
            return os << "Warrior";
        default:
            throw std::invalid_argument("Unsupported CharacterClass value for streaming.");
    }
}

std::istream& operator>>(std::istream& is, CharacterClass& characterClass) {
    std::string choice;
    is >> choice;
    std::cout << choice;
    if(choice == "Human") {
        characterClass = CharacterClass::Human;
    } else if(choice == "Mage") {
        characterClass = CharacterClass::Mage;
    } else if(choice == "Warrior") {
        characterClass = CharacterClass::Warrior;
    } else {
        throw std::invalid_argument("Invalid character class choice");
    }

    return is;
}