#ifndef FMI_COURSE_PROJECT_DND_TREASURETILE_HPP
#define FMI_COURSE_PROJECT_DND_TREASURETILE_HPP

#include "Tile.hpp"
#include "../../item/ItemType.hpp"

/**
 * @class TreasureTile
 * @ingroup Map
 * @brief Represents a tile containing a treasure item.
 */
class TreasureTile : public Tile {
public:
    /**
     * @brief Constructs a treasure tile with an item pointer and type.
     * @param item Pointer to the item.
     * @param type Type of the item.
     */
    TreasureTile(Item* item, ItemType type);

    /**
     * @brief Constructs a treasure tile by copying an item.
     * @param item The item.
     * @param type The item type.
     */
    TreasureTile(const Item& item, ItemType type);

    /**
     * @brief Copy constructor.
     */
    TreasureTile(const TreasureTile& other);

    /**
     * @brief Copy assignment operator.
     */
    TreasureTile& operator=(const TreasureTile& other);

    /**
     * @brief Generates a random treasure tile based on level.
     * @param level The current game level.
     * @return A new TreasureTile pointer.
     */
    static Tile* generateRandomTreasureTile(unsigned level);

    /**
     * @brief Let's player equip item.
     * @param character The player character.
     */
    void apply(Character &character) override;

    /**
     * @brief Let's player equip item in graphical interface.
     * @param character The player character.
     * @param window The render window context.
     */
    void apply(Character &character, sf::RenderWindow& window) override;

    /**
     * @brief Gets the display character representing a treasure.
     * @return ASCII character representing a treasure tile - T.
     */
    char getDisplayCharacter() const override;

    /**
     * @brief Replaces the tile after the treasure is collected.
     * @return A new Tile (EmptyTile).
     */
    Tile *changeOnExpended() override;

    /**
     * @brief Serializes the treasure tile.
     * @param os The output stream.
     */
    void serialize(std::ostream &os) const override;

    /**
     * @brief Clones the treasure tile.
     * @return A new TreasureTile instance.
     */
    Tile *clone() const override;

    /**
     * @brief Destructor (cleans up the item).
     */
    ~TreasureTile() override;

protected:
    /**
     * @brief Gets the SFML color used to render the treasure tile.
     * @return Color for treasure tile - sf::Color::Yellow.
     */
    sf::Color getColor() override;

private:
    Item* item;           ///< Pointer to the item stored in the tile.
    ItemType type;        ///< The type of item.

    /**
     * @brief Computes bonus based on game level.
     * @param level The current level.
     * @return The computed bonus.
     */
    static double getBonusFromLevel(unsigned level);
};

#endif
