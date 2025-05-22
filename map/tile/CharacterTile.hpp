#ifndef FMI_COURCE_PROJECT_DND_CHARACTERTILE_HPP
#define FMI_COURCE_PROJECT_DND_CHARACTERTILE_HPP

#include "Tile.hpp"

class CharacterTile : public Tile {
public:
    void apply(Character &otherCharacter) override;
    char getDisplayCharacter() const override;
    Tile *clone() const override;
    ~CharacterTile() override = default;
};


#endif
