#ifndef FMI_COURSE_PROJECT_DND_EMPTYTILE_HPP
#define FMI_COURSE_PROJECT_DND_EMPTYTILE_HPP

#include "Tile.hpp"

/**
 * @class EmptyTile
 * @ingroup Map
 * @brief Represents an empty walkable tile.
 */
class EmptyTile : public Tile {
public:
    /**
     * @brief Gets the terminal display character.
     * @return ASCII character representing an empty tile - .
     */
    char getDisplayCharacter() const override;

    /**
     * @brief Indicates that this tile is empty.
     * @return True.
     */
    bool isEmpty() override;

    /**
     * @brief Clones the tile.
     * @return New instance of EmptyTile.
     */
    Tile* clone() const override;

    /**
     * @brief Destructor.
     */
    ~EmptyTile() override = default;

protected:
    /**
     * @brief Gets the color used for SFML rendering.
     * @return Color for empty tile - sf::Color::Black.
     */
    sf::Color getColor() override;
};

#endif
