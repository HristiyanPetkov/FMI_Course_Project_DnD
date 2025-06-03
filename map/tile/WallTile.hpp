#ifndef FMI_COURSE_PROJECT_DND_WALLTILE_HPP
#define FMI_COURSE_PROJECT_DND_WALLTILE_HPP


#include "Tile.hpp"

class WallTile : public Tile {
public:
    char getDisplayCharacter() const override;
    Tile *changeOnExpended() override;
    Tile *clone() const override;
    ~WallTile() override = default;

protected:
    sf::Color getColor() override;
};


#endif
