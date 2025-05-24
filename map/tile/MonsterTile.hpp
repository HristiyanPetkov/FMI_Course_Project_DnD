#ifndef FMI_COURSE_PROJECT_DND_MONSTERTILE_HPP
#define FMI_COURSE_PROJECT_DND_MONSTERTILE_HPP


#include "Tile.hpp"
#include "../../monster/Monster.hpp"

class MonsterTile : public Tile {
public:
    explicit MonsterTile(const Monster& monster);
    void apply(Character &character) override;
    char getDisplayCharacter() const override;
    Tile *changeOnExpended() override;
    void serialize(std::ostream &os) const override;
    Tile *clone() const override;
    ~MonsterTile() override = default;
private:
    Monster monster;
};


#endif
