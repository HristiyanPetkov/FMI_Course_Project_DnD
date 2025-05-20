#include <catch2/catch_all.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "../item/Item.hpp"
#include "../item/Armor.hpp"
#include "../item/Spell.hpp"
#include "../item/Weapon.hpp"

TEST_CASE("Item base class functionality", "[Item]") {
    Item item("Generic", 20.0);

    SECTION("Apply bonus to damage") {
        REQUIRE_THAT(item.applyBonus(100.0), Catch::Matchers::WithinRel(20, 1e-4));
    }

    SECTION("Clone creates a copy") {
        Item* copy = item.clone();
        REQUIRE(copy != &item);
        REQUIRE(copy->applyBonus(100.0) == item.applyBonus(100.0));
        delete copy;
    }
}

TEST_CASE("Armor class functionality", "[Armor]") {
    Armor armor("Chainmail", 30.0);

    SECTION("Apply bonus returns reduced damage") {
        REQUIRE_THAT(armor.applyBonus(100.0), Catch::Matchers::WithinRel(70, 1e-4));
    }

    SECTION("Clone creates a new Armor") {
        Item* copy = armor.clone();
        REQUIRE(copy != &armor);
        REQUIRE(copy->applyBonus(100.0) == armor.applyBonus(100.0));
        delete copy;
    }
}

TEST_CASE("Weapon class functionality", "[Weapon]") {
    Weapon weapon("Sword", 60);

    SECTION("Apply bonus increases damage") {
        REQUIRE_THAT(weapon.applyBonus(100.0), Catch::Matchers::WithinRel(160, 1e-4));
    }

    SECTION("Clone creates a new Spell") {
        Item* copy = weapon.clone();
        REQUIRE(copy != &weapon);
        REQUIRE(copy->applyBonus(100.0) == weapon.applyBonus(100.0));
        delete copy;
    }
}

TEST_CASE("Spell class functionality", "[Spell]") {
    Spell spell("Fireball", 50.0);

    SECTION("Apply bonus increases damage") {
        REQUIRE_THAT(spell.applyBonus(100.0), Catch::Matchers::WithinRel(150, 1e-4));
    }

    SECTION("Clone creates a new Spell") {
        Item* copy = spell.clone();
        REQUIRE(copy != &spell);
        REQUIRE(copy->applyBonus(100.0) == spell.applyBonus(100.0));
        delete copy;
    }
}