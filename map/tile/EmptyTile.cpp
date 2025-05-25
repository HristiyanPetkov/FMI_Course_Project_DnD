#include "EmptyTile.hpp"

void EmptyTile::apply(Character &character) {}

char EmptyTile::getDisplayCharacter() const {
    return '.';
}

Tile *EmptyTile::clone() const {
    return new EmptyTile();
}

bool EmptyTile::isEmpty() {
    return true;
}

void EmptyTile::renderSFML(sf::RenderWindow &window, float x, float y, float tileSize) {
    sf::RectangleShape shape(sf::Vector2f(tileSize, tileSize));
    shape.setPosition({x, y});
    shape.setFillColor(sf::Color::White);
    shape.setOutlineThickness(1.f);
    shape.setOutlineColor(sf::Color::Black);

    window.draw(shape);
}
