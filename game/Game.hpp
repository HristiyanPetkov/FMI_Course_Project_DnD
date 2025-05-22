#ifndef FMI_COURCE_PROJECT_DND_GAME_HPP
#define FMI_COURCE_PROJECT_DND_GAME_HPP


#include "../map/GameMap.hpp"

class Game {
public:
    explicit Game(unsigned level = 1);
    explicit Game(const Character& character, unsigned level = 1);
    void start();
private:
    unsigned level;
    Character player;
    GameMap currentMap;
};


#endif
