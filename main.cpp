#include <iostream>
#include "map/GameMap.hpp"

int main() {
    GameMap(Character("Pesho", CharacterClass::Human), 1).render();

    return 0;
}
