#ifndef FMI_COURCE_PROJECT_DND_TREASURETILE_HPP
#define FMI_COURCE_PROJECT_DND_TREASURETILE_HPP


#include "Tile.hpp"

class TreasureTile : public Tile {
public:
    explicit TreasureTile(Item* item);
    explicit TreasureTile(const Item& item);
    TreasureTile(const TreasureTile& other);
    TreasureTile& operator=(const TreasureTile& other);
    static Tile* generateRandomTreasureTile(unsigned level);

    void apply(Character &character) override;
    char getDisplayCharacter() const override;
    Tile *clone() const override;
    ~TreasureTile() override;
private:
    Item* item;
};


#endif
