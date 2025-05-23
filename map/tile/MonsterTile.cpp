#include "MonsterTile.hpp"
#include "../../battle/BattleSystem.hpp"
#include "EmptyTile.hpp"

MonsterTile::MonsterTile(const Monster &monster)
: monster(monster) {}

void MonsterTile::apply(Character &character) {
    BattleSystem::battle(character, monster);
}

char MonsterTile::getDisplayCharacter() const {
    return 'M';
}

Tile *MonsterTile::changeOnExpended() {
    if(!monster.isAlive()) {
        delete this;
        return new EmptyTile();
    }
    return this;
}

Tile *MonsterTile::clone() const {
    return new MonsterTile(*this);
}

void MonsterTile::serialize(std::ostream &os) {
    os << getDisplayCharacter() << " ";
    monster.serialize(os);
}
