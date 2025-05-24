#ifndef FMI_COURSE_PROJECT_DND_GAMEMAPFACTORY_HPP
#define FMI_COURSE_PROJECT_DND_GAMEMAPFACTORY_HPP


#include "GameMap.hpp"

class GameMapFactory {
public:
    static GameMap createFromLevel(unsigned level);
//    static GameMap createFromFile(const std::string& path);
};


#endif
