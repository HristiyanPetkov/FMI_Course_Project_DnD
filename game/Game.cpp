#include "Game.hpp"
#include "../map/GameMapFactory.hpp"
#include "../map/Direction.hpp"
#include "../character/CharacterFactory.hpp"
#include "InputCommand.hpp"

Game::Game(unsigned int level)
: level(level),
  player(CharacterFactory::createCharacterFromUserInput()),
  currentMap(GameMapFactory::createFromLevel(level)) {}

Game::Game(const Character &character, unsigned int level)
: level(level), player(character), currentMap(GameMapFactory::createFromLevel(level)) {}

void Game::start() {
//    Direction directionInput;
    InputCommand command;
    while(player.isAlive()) {
//        system("clear");
        currentMap.render();
        try {
            std::cin >> command;
            std::cin.ignore();
            switch(command) {

                case InputCommand::MOVE_UP:
                case InputCommand::MOVE_LEFT:
                case InputCommand::MOVE_DOWN:
                case InputCommand::MOVE_RIGHT:
                    currentMap.move(player, commandToDirection(command));
                    if(currentMap.onNextLevelField()) {
                        std::cout << "Generating new map" << std::endl;
                        currentMap = GameMapFactory::createFromLevel(++level);
                    }
                    break;
                case InputCommand::PRINT_CHARACTER:
                    player.print();
                    break;
                case InputCommand::EXIT:
//                    save();
                    return;
            }
        } catch(std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
    std::cout << "You Died" << std::endl;
}
