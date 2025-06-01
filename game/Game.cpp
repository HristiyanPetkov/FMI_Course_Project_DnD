#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>
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

void Game::startSFML(sf::RenderWindow& window) {
    sf::View map, characterInfo, menu;

    map.setViewport(sf::FloatRect({0.f, 0.f}, {0.75f, 1.f}));
    characterInfo.setViewport(sf::FloatRect({0.75f, 0.f}, {0.25f, 0.35f}));
    menu.setViewport(sf::FloatRect({0.75f, 0.35f}, {0.25f, 0.65f}));

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
                    case sf::Keyboard::Scancode::Escape: command = InputCommand::EXIT; break;
                    default: break;
                }
            }

            if (const auto resized = event->getIf<sf::Event::Resized>()) {
                sf::FloatRect visibleArea({0, 0}, sf::Vector2f(resized->size));
                window.setView(sf::View(visibleArea));
            }
        }

        try {
            switch (command) {
                case InputCommand::MOVE_UP:
                case InputCommand::MOVE_LEFT:
                case InputCommand::MOVE_DOWN:
                case InputCommand::MOVE_RIGHT:
                    window.setView(map);
                    currentMap.move(player, commandToDirection(command), window);
                    if (currentMap.onNextLevelField()) {
                        player.levelUpSFML(window);
                        std::cout << "Generating new map..." << std::endl;
                        currentMap = GameMapFactory::createFromLevel(++level);
                    }
                    break;
                case InputCommand::EXIT:
                    save("savefile.dat");
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
        window.setView(map);
        currentMap.renderSFML(window);
        window.setView(characterInfo);
        player.printSFML(window);
        window.setView(menu);
        visualizeMenu(window);
        window.display();
    }

    if(!player.isAlive()) {
        std::cout << "You Died" << std::endl;
    }
    updateHighScores();
}

void Game::checkForNextLevel() {
    if(currentMap.onNextLevelField()) {
        player.levelUp();
        std::cout << "Generating new map" << std::endl;
        currentMap = GameMapFactory::createFromLevel(++level);
    }
}

void Game::visualizeMenu(sf::RenderWindow& window) {
    sf::Font font("resources/text_fonts/montserrat/Montserrat-Black.otf");
    sf::Text text(font);

    text.setCharacterSize(60);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f{ window.getView().getSize() / 8.f });

    std::wstring str = L"Move up: W/↑\n"
                      "Move left: A/←\n"
                      "Move down: S/↓\n"
                      "Move right: D/→\n"
                      "\n\n"
                      "Exit: Esc\n";

    text.setString(str);
    window.draw(text);
}
