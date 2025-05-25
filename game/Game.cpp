#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Game.hpp"
#include "../map/GameMapFactory.hpp"
#include "../map/Direction.hpp"
#include "../character/CharacterFactory.hpp"
#include "InputCommand.hpp"
#include "../highScore/HighScoreManager.hpp"

Game::Game()
: level(0), player(), currentMap() {}

Game::Game(unsigned int level)
: level(level),
  player(CharacterFactory::createCharacterFromUserInput()),
  currentMap(GameMapFactory::createFromLevel(level)) {}

Game::Game(const Character &character, unsigned int level)
: level(level), player(character), currentMap(GameMapFactory::createFromLevel(level)) {}

void Game::start() {
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
                        player.levelUp();
                        std::cout << "Generating new map" << std::endl;
                        currentMap = GameMapFactory::createFromLevel(++level);
                    }
                    break;
                case InputCommand::PRINT_CHARACTER:
                    player.print();
                    break;
                case InputCommand::EXIT:
                    std::cout << "Do you wish to save the game?(y):";
                    char answer;
                    std::cin >> answer;
                    std::cin.ignore();
                    if(answer == 'y') {
                        std::cout << "Enter file path:";
                        std::string filePath;
                        std::getline(std::cin, filePath);
                        save(filePath);
                    }
                    return;
            }
        } catch(std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
    std::cout << "You Died" << std::endl;
    updateHighScores();
}

void Game::save(const std::string& filePath) {
    std::ofstream file(filePath, std::ios::trunc);
    if(!file) {
        throw std::runtime_error("cannot open file for writing");
    }
    file << level << std::endl;
    player.serialize(file);
    currentMap.serialize(file);
}

Game Game::loadFromFile(const std::string &filePath) {
    std::ifstream file(filePath);
    if(!file) {
        throw std::runtime_error("Cannot open file for reading");
    }
    unsigned level;
    Character player;
    GameMap map;
    Game game;

    file >> level;
    player.deserialize(file);
    map.deserialize(file);

    game.level = level;
    game.player = player;
    game.currentMap = map;
    return game;
}

void Game::updateHighScores() {
    HighScoreManager::saveScore(level, player);
}

void Game::startSFML() {
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 0;
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML Grid Game", sf::State::Windowed, settings);
    window.setFramerateLimit(30);

    while (window.isOpen() && player.isAlive()) {
        InputCommand command = InputCommand::NONE;
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                switch (keyPressed->scancode) {
                    case sf::Keyboard::Scancode::Up:
                    case sf::Keyboard::Scancode::W: command = InputCommand::MOVE_UP; break;
                    case sf::Keyboard::Scancode::Left:
                    case sf::Keyboard::Scancode::A: command = InputCommand::MOVE_LEFT; break;
                    case sf::Keyboard::Scancode::Down:
                    case sf::Keyboard::Scancode::S: command = InputCommand::MOVE_DOWN; break;
                    case sf::Keyboard::Scancode::Right:
                    case sf::Keyboard::Scancode::D: command = InputCommand::MOVE_RIGHT; break;
                    case sf::Keyboard::Scancode::C: command = InputCommand::PRINT_CHARACTER; break;
                    case sf::Keyboard::Scancode::Escape: command = InputCommand::EXIT; break;
                    default: break;
                }
            }
        }

        try {
            switch (command) {
                case InputCommand::MOVE_UP:
                case InputCommand::MOVE_LEFT:
                case InputCommand::MOVE_DOWN:
                case InputCommand::MOVE_RIGHT:
                    currentMap.move(player, commandToDirection(command));
                    if (currentMap.onNextLevelField()) {
                        player.levelUp();
                        std::cout << "Generating new map..." << std::endl;
                        currentMap = GameMapFactory::createFromLevel(++level);
                    }
                    break;

                case InputCommand::PRINT_CHARACTER:
                    // You might want to render this info in the window instead
                    player.print();
                    break;

                case InputCommand::EXIT:
                    // No prompt for file path in GUI version (unless using text input UI)
                    save("savefile.dat"); // replace with proper path handling later
                    window.close();
                    return;

                case InputCommand::NONE:
                default:
                    break;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        window.clear(sf::Color::Black);
        currentMap.renderSFML(window);
//        window.setView(window.getDefaultView());
        window.display();
    }

    std::cout << "You Died" << std::endl;
    updateHighScores();
}

void Game::checkForNextLevel() {
    if(currentMap.onNextLevelField()) {
        player.levelUp();
        std::cout << "Generating new map" << std::endl;
        currentMap = GameMapFactory::createFromLevel(++level);
    }
}
