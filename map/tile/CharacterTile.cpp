#include "CharacterTile.hpp"

void CharacterTile::apply(Character &otherCharacter) {
    otherCharacter.print();
}

char CharacterTile::getDisplayCharacter() const {
    return 'C';
}

Tile *CharacterTile::clone() const {
    return new CharacterTile(*this);
}

void CharacterTile::renderSFML(sf::RenderWindow &window, float x, float y, float tileSize) {
    sf::RectangleShape shape(sf::Vector2f(tileSize, tileSize));
    shape.setPosition({x, y});
    shape.setFillColor(sf::Color::Green);
    shape.setOutlineThickness(1.f);
    shape.setOutlineColor(sf::Color::Black);

    window.draw(shape);
}
