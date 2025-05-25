#include "WallTile.hpp"

void WallTile::apply(Character &character) {}

char WallTile::getDisplayCharacter() const {
    return '#';
}

Tile *WallTile::clone() const {
    return new WallTile();
}

Tile *WallTile::changeOnExpended() {
    return this;
}

void WallTile::renderSFML(sf::RenderWindow &window, float x, float y, float tileSize) {
    sf::RectangleShape shape(sf::Vector2f(tileSize, tileSize));
    shape.setPosition({x, y});
    shape.setFillColor(sf::Color::Black);
    shape.setOutlineThickness(1.f);
    shape.setOutlineColor(sf::Color::Black);

    window.draw(shape);
}
