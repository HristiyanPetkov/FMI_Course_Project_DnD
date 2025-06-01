#ifndef FMI_COURSE_PROJECT_DND_GAME_HPP
#define FMI_COURSE_PROJECT_DND_GAME_HPP


#include "../map/GameMap.hpp"
#include "../character/Character.hpp"

enum class GameDisplay { Terminal, SFML };

class Game {
public:
    Game();
    explicit Game(unsigned level);
    explicit Game(const Character& character, unsigned level = 1);

    void start();
    static Game loadFromFile(const std::string& filePath);
    void startSFML(sf::RenderWindow& window);
private:
    unsigned level;
    Character player;
    GameMap currentMap;
    void save(const std::string& filePath);
    void updateHighScores();

    void checkForNextLevel();

    void visualizeMenu(sf::RenderWindow& window);
};


#endif
