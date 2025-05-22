#ifndef FMI_COURCE_PROJECT_DND_MONSTERTILE_HPP
#define FMI_COURCE_PROJECT_DND_MONSTERTILE_HPP


#include "Tile.hpp"
#include "../../monster/Monster.hpp"

class MonsterTile : public Tile {
public:
    explicit MonsterTile(const Monster& monster);
    void apply(Character &character) override;
    char getDisplayCharacter() const override;
    Tile *clone() const override;
    ~MonsterTile() override = default;
private:
    Monster monster;
};


#endif
