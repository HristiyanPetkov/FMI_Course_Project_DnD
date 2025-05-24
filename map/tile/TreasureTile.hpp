#ifndef FMI_COURSE_PROJECT_DND_TREASURETILE_HPP
#define FMI_COURSE_PROJECT_DND_TREASURETILE_HPP


#include "Tile.hpp"
#include "../../item/ItemType.hpp"

class TreasureTile : public Tile {
public:
    TreasureTile(Item* item, ItemType type);
    TreasureTile(const Item& item, ItemType type);
    TreasureTile(const TreasureTile& other);
    TreasureTile& operator=(const TreasureTile& other);
    static Tile* generateRandomTreasureTile(unsigned level);

    void apply(Character &character) override;
    char getDisplayCharacter() const override;
    Tile *changeOnExpended() override;
    void serialize(std::ostream &os) const override;
    Tile *clone() const override;
    ~TreasureTile() override;
private:
    Item* item;
    ItemType type;
    static double getBonusFromLevel(unsigned level);
};


#endif
