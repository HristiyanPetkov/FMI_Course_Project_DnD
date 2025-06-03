#ifndef FMI_COURSE_PROJECT_DND_GAMEMAP_HPP
#define FMI_COURSE_PROJECT_DND_GAMEMAP_HPP

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "Direction.hpp"
#include "../item/Item.hpp"
#include "../monster/Monster.hpp"
#include "../character/Character.hpp"
#include "tile/Tile.hpp"

/**
 * @defgroup Map
 * @brief Map and tile types
 * @details GameMap object and all tiles associated with the map
 */

/**
 * @class GameMap
 * @ingroup Map
 * @brief Represents the playable game map.
 *
 * Manages the map layout, player movement, rendering, and serialization logic.
 */
class GameMap {
public:
    /**
     * @brief Default constructor.
     */
    GameMap();

    /**
     * @brief Constructs a GameMap for a given level.
     * @param level The current game level.
     */
    explicit GameMap(unsigned level);

    /**
     * @brief Copy constructor.
     * @param other Map to copy.
     */
    GameMap(const GameMap& other);

    /**
     * @brief Assignment operator.
     * @param other Map to copy from.
     * @return Reference to this map.
     */
    GameMap& operator=(const GameMap& other);

    /**
     * @brief Destructor.
     */
    ~GameMap();

    /**
     * @brief Renders the map to the console.
     */
    void render();

    /**
     * @brief Moves the character in the specified direction in terminal mode.
     * @param character The player character.
     * @param direction The direction to move.
     */
    void move(Character& character, Direction direction);

    /**
     * @brief Checks if the character is on a tile that triggers the next level.
     * @return True if on next-level field, false otherwise.
     */
    bool onNextLevelField() const;

    /**
     * @brief Serializes the map to an output stream.
     * @param os The output stream.
     */
    void serialize(std::ostream &os) const;

    /**
     * @brief Deserializes the map from an input stream.
     * @param is The input stream.
     */
    void deserialize(std::istream &is);

    /**
     * @brief Renders the map graphically using SFML.
     * @param window The render window.
     */
    void renderSFML(sf::RenderWindow& window);

    /**
     * @brief Moves the character using graphical input.
     * @param character The player character.
     * @param direction The direction to move.
     * @param window The SFML window.
     */
    void move(Character& character, Direction direction, sf::RenderWindow& window);

private:
    size_t width;                         ///< Width of the map.
    size_t height;                        ///< Height of the map.
    size_t numberOfMonsters;              ///< Number of monsters on the map.
    size_t numberOfTreasures;             ///< Number of treasures on the map.
    std::vector<std::vector<Tile*>> map;  ///< 2D grid of map tiles.
    size_t characterX;                    ///< X position of the character.
    size_t characterY;                    ///< Y position of the character.

    /**
     * @brief Swaps the internal state with another GameMap.
     * @param other The other GameMap.
     */
    void swap(GameMap& other);

    /**
     * @brief Sets parameters like size and difficulty based on level.
     * @param level Current level.
     */
    void calculateLevelParameters(unsigned level);

    /**
     * @brief Fills the map with empty tiles and walls.
     */
    void fillMapWithEmptyAndWalls();

    /**
     * @brief Places the character on the starting tile.
     */
    void setStartingCharacterTile();

    /**
     * @brief Populates the map with monsters and treasures.
     * @param level The game level.
     */
    void placeRandomElements(unsigned level);

    /**
     * @brief Gets a list of valid positions where entities can be placed.
     * @return A vector of valid (x, y) coordinates.
     */
    std::vector<std::pair<size_t, size_t>> getValidPositions();

    /**
     * @brief Checks whether movement in a direction is valid.
     * @param direction The direction to check.
     * @return True if movement is allowed.
     */
    bool canMove(Direction direction);

    /**
     * @brief Moves the character on the map in terminal mode.
     * @param character The player character.
     * @param direction The direction to move.
     */
    void movePlayer(Character& character, Direction direction);

    /**
     * @brief Moves the character on the map in graphical mode.
     * @param character The player character.
     * @param direction The direction to move.
     * @param window The SFML render window.
     */
    void movePlayer(Character& character, Direction direction, sf::RenderWindow& window);
};

#endif
