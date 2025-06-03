#ifndef FMI_COURSE_PROJECT_DND_TILE_HPP
#define FMI_COURSE_PROJECT_DND_TILE_HPP

#include "SFML/Graphics.hpp"
#include "../../character/Character.hpp"

/**
 * @class Tile
 * @ingroup Map
 * @brief Abstract base class for tiles on the game map.
 *
 * Defines basic behavior for interaction and rendering.
 */
class Tile {
public:
    /**
     * @brief Applies the tile effect to a character.
     * @param character The character stepping on the tile.
     */
    virtual void apply(Character& character);

    /**
     * @brief Gets the character representation for terminal display.
     * @return A char symbol representing the tile.
     */
    virtual char getDisplayCharacter() const = 0;

    /**
     * @brief Checks if the tile is empty.
     * @return True if empty, false otherwise.
     */
    virtual bool isEmpty();

    /**
     * @brief Returns a different tile after the current tile is used (optional override).
     * @return A new Tile pointer.
     */
    virtual Tile* changeOnExpended();

    /**
     * @brief Serializes tile to output stream.
     * @param os The output stream.
     */
    virtual void serialize(std::ostream& os) const;

    /**
     * @brief Deserializes a tile from an input stream.
     * @param is The input stream.
     * @return A pointer to the deserialized Tile.
     */
    static Tile* deserialize(std::istream &is);

    /**
     * @brief Virtual destructor.
     */
    virtual ~Tile() = default;

    /**
     * @brief Clones the tile (deep copy).
     * @return A new cloned Tile instance.
     */
    virtual Tile* clone() const = 0;

    /**
     * @brief Renders the tile using SFML.
     * @param window Render window.
     * @param x X position on grid.
     * @param y Y position on grid.
     * @param tileSizeX Width of the tile.
     * @param tileSizeY Height of the tile.
     */
    void renderSFML(sf::RenderWindow& window, float x, float y, float tileSizeX, float tileSizeY);

    /**
     * @brief Applies the tile effect to a character in SFML mode.
     * @param character The character.
     * @param window SFML window context.
     */
    virtual void apply(Character& character, sf::RenderWindow& window);

protected:
    /**
     * @brief Gets the SFML color used for rendering.
     * @return An SFML color.
     */
    virtual sf::Color getColor() = 0;
};

#endif
