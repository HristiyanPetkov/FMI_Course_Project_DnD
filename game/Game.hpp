#ifndef FMI_COURCE_PROJECT_DND_GAME_HPP
#define FMI_COURCE_PROJECT_DND_GAME_HPP


#include "../map/GameMap.hpp"
#include "../character/Character.hpp"

class Game {
public:
    Game();
    explicit Game(unsigned level);
    explicit Game(const Character& character, unsigned level = 1);
    void start();
    static Game loadFromFile(const std::string& filePath);
private:
    unsigned level;
    Character player;
    GameMap currentMap;
    void save(const std::string& filePath);
};


#endif
