#ifndef FMI_COURSE_PROJECT_DND_GAMEMAPFACTORY_HPP
#define FMI_COURSE_PROJECT_DND_GAMEMAPFACTORY_HPP

#include "GameMap.hpp"

/**
 * @class GameMapFactory
 * @ingroup Map
 * @brief Factory for generating GameMap objects.
 */
class GameMapFactory {
public:
    /**
     * @brief Creates a GameMap for a specific level.
     * @param level The level of the game.
     * @return Initialized GameMap object.
     */
    static GameMap createFromLevel(unsigned level);
};

#endif
