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

void MonsterTile::serialize(std::ostream &os) const {
    os << getDisplayCharacter() << " ";
    monster.serialize(os);
}

void MonsterTile::renderSFML(sf::RenderWindow &window, float x, float y, float tileSize) {
    sf::RectangleShape shape(sf::Vector2f(tileSize, tileSize));
    shape.setPosition({x, y});
    shape.setFillColor(sf::Color::Red);
    shape.setOutlineThickness(1.f);
    shape.setOutlineColor(sf::Color::Black);

    window.draw(shape);
}
