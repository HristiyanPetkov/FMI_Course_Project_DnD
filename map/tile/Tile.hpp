#ifndef FMI_COURCE_PROJECT_DND_TILE_HPP
#define FMI_COURCE_PROJECT_DND_TILE_HPP
#include "../../character/Character.hpp"


class Tile {
public:
    virtual void apply(Character& character) = 0;
    virtual char getDisplayCharacter() const = 0;
    virtual bool isEmpty();
    virtual Tile* clone() const = 0;
    virtual ~Tile() = default;
};


#endif
