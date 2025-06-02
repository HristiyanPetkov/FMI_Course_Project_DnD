#ifndef FMI_COURSE_PROJECT_DND_CHARACTERTILE_HPP
#define FMI_COURSE_PROJECT_DND_CHARACTERTILE_HPP

#include "Tile.hpp"

/**
 * @class CharacterTile
 * @ingroup Map
 * @brief Represents a tile occupied by a character.
 */
class CharacterTile : public Tile {
public:
    /**
     * @brief Applies interaction when another character steps on this tile.
     * @note Currently the game supports only one character.
     * @param otherCharacter The character interacting with the tile.
     */
    void apply(Character &otherCharacter) override;

    /**
     * @brief Gets the display character representing a character on the map.
     * @return ASCII character representing an empty tile - C.
     */
    char getDisplayCharacter() const override;

    /**
     * @brief Clones the character tile.
     * @return A new CharacterTile instance.
     */
    Tile *clone() const override;

    /**
     * @brief Destructor.
     */
    ~CharacterTile() override = default;

protected:
    /**
     * @brief Gets the SFML color used to render the character tile.
     * @return Color for character tile - sf::Color::Green.
     */
    sf::Color getColor() override;
};

#endif
