#ifndef FMI_COURSE_PROJECT_DND_WALLTILE_HPP
#define FMI_COURSE_PROJECT_DND_WALLTILE_HPP


#include "Tile.hpp"

class WallTile : public Tile {
public:
    void apply(Character &character) override;
    char getDisplayCharacter() const override;
    Tile *changeOnExpended() override;
    Tile *clone() const override;
    ~WallTile() override = default;
};


#endif
