#ifndef FMI_COURCE_PROJECT_DND_WALLTILE_HPP
#define FMI_COURCE_PROJECT_DND_WALLTILE_HPP


#include "Tile.hpp"

class WallTile : public Tile {
public:
    void apply(Character &character) override;
    char getDisplayCharacter() const override;
    Tile *clone() const override;
    ~WallTile() override = default;
};


#endif
