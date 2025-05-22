#include "Game.hpp"
#include "../map/GameMapFactory.hpp"
#include "../character/CharacterFactory.hpp"

Game::Game(unsigned int level)
: level(level),
  player(CharacterFactory::createCharacterFromUserInput()),
  currentMap(GameMapFactory::createFromLevel(level)) {}

Game::Game(const Character &character, unsigned int level)
: level(level), player(character), currentMap(GameMapFactory::createFromLevel(level)) {}

void Game::start() {
    Direction directionInput;
    while(player.isAlive()) {
//        system("clear");
        currentMap.render();

        try {
            std::cin >> directionInput;
            std::cin.ignore();

            currentMap.move(player, directionInput);
            if(currentMap.onNextLevelField()) {
                std::cout << "Generating new map" << std::endl;
                currentMap = GameMapFactory::createFromLevel(++level);
            }
        } catch(std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
    std::cout << "You Died" << std::endl;
}
