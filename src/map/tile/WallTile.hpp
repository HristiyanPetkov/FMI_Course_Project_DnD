#ifndef FMI_COURSE_PROJECT_DND_WALLTILE_HPP
#define FMI_COURSE_PROJECT_DND_WALLTILE_HPP

#include "Tile.hpp"

/**
 * @class WallTile
 * @ingroup Map
 * @brief Represents an impassable wall tile.
 */
class WallTile : public Tile {
public:
    /**
     * @brief Gets the terminal display character.
     * @return ASCII character representing a wall tile - #.
     */
    char getDisplayCharacter() const override;

    /**
     * @brief Returns a new tile if the wall is destroyed or changed.
     * @note The current implementation doesn't support mutating wall tiles.
     * @return A different Tile instance.
     */
    Tile* changeOnExpended() override;

    /**
     * @brief Clones the tile.
     * @return New instance of WallTile.
     */
    Tile* clone() const override;

    /**
     * @brief Destructor.
     */
    ~WallTile() override = default;

protected:
    /**
     * @brief Gets the color used for SFML rendering.
     * @return Color for wall tile - sf::Color::White.
     */
    sf::Color getColor() override;
};

#endif
