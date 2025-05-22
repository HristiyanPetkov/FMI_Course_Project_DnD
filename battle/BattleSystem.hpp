#ifndef FMI_COURCE_PROJECT_DND_BATTLESYSTEM_HPP
#define FMI_COURCE_PROJECT_DND_BATTLESYSTEM_HPP


#include "../character/Character.hpp"
#include "../monster/Monster.hpp"


class BattleSystem {
public:
    static bool battle(Character& character, Monster& monster);
};


#endif
