#ifndef FMI_COURCE_PROJECT_DND_EMPTYTILE_HPP
#define FMI_COURCE_PROJECT_DND_EMPTYTILE_HPP


#include "Tile.hpp"

class EmptyTile : public Tile {
public:
    void apply(Character &character) override;
    char getDisplayCharacter() const override;
    bool isEmpty() override;
    Tile *clone() const override;
    ~EmptyTile() override = default;
};


#endif
