#include "GameMapFactory.hpp"

GameMap GameMapFactory::createFromLevel(unsigned int level) {
    return GameMap(level);
}
