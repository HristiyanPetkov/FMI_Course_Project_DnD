#ifndef FMI_COURSE_PROJECT_DND_MONSTERTILE_HPP
#define FMI_COURSE_PROJECT_DND_MONSTERTILE_HPP

#include "Tile.hpp"
#include "../../monster/Monster.hpp"

/**
 * @class MonsterTile
 * @ingroup Map
 * @brief Represents a tile containing a monster.
 */
class MonsterTile : public Tile {
public:
    /**
     * @brief Constructs the tile with a given monster.
     * @param monster The monster to be placed on this tile.
     */
    explicit MonsterTile(const Monster& monster);

    /**
     * @brief Applies the monster's effects to the character (battle).
     * @param character The player character.
     */
    void apply(Character &character) override;

    /**
     * @brief Applies effects using the SFML window (e.g., graphical battle).
     * @param character The player character.
     * @param window The render window context.
     */
    void apply(Character& character, sf::RenderWindow& window) override;

    /**
     * @brief Gets the display character representing a monster on the map.
     * @return ASCII character representing a monster tile - M.
     */
    char getDisplayCharacter() const override;

    /**
     * @brief Replaces the monster tile once the monster is defeated.
     * @return A new Tile (usually an EmptyTile).
     */
    Tile *changeOnExpended() override;

    /**
     * @brief Serializes the monster tile.
     * @param os The output stream.
     */
    void serialize(std::ostream &os) const override;

    /**
     * @brief Clones the monster tile.
     * @return A new MonsterTile instance.
     */
    Tile *clone() const override;

    /**
     * @brief Destructor.
     */
    ~MonsterTile() override = default;

protected:
    /**
     * @brief Gets the SFML color used to render the monster tile.
     * @return Color for monster tile - sf::Color::Red.
     */
    sf::Color getColor() override;

private:
    Monster monster;  ///< Monster instance on this tile.
};

#endif
