#include "CharacterFactory.hpp"

Character CharacterFactory::createCharacterFromUserInput() {
    std::cout << "Enter character name :";
    std::string name;
    std::cin >> name;
    std::cout << "Pick a class: 1. Human, 2. Mage, 3. Warrior" << std::endl;
    CharacterClass characterClass;
    std::cin >> characterClass;
    return Character(name, characterClass);
}
