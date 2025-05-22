#include "MonsterTile.hpp"
#include "../../battle/BattleSystem.hpp"

MonsterTile::MonsterTile(const Monster &monster)
: monster(monster) {}

void MonsterTile::apply(Character &character) {
    BattleSystem::battle(character, monster);
}

char MonsterTile::getDisplayCharacter() const {
    return 'M';
}

Tile *MonsterTile::clone() const {
    return new MonsterTile(*this);
}
