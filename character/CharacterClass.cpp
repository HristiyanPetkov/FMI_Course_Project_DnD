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
//    int choice;
//    is >> choice;
//    switch(choice) {
//        case 1:
//            characterClass = CharacterClass::Human;
//            break;
//        case 2:
//            characterClass = CharacterClass::Mage;
//            break;
//        case 3:
//            characterClass = CharacterClass::Warrior;
//            break;
//        default:
//            throw std::invalid_argument("Invalid character class choice");
//    }
    std::string choice;
    is >> choice;
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