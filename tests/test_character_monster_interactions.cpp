#include <catch2/catch_all.hpp>
#include "../monster/Monster.hpp"
#include "../character/Character.hpp"

TEST_CASE("Characters and Monsters deal damage to each other ", "[Character, Monster]") {
    Monster dragon("Dragon", 1);
    Character hero("Hero", CharacterClass::Human);
    hero.dealDamage(dragon, Character::AttackType::WEAPON);
    dragon.dealDamage(hero);
    REQUIRE_THAT(dragon.getCurrentHealth(), Catch::Matchers::WithinRel(4.1, 1e-4));
    REQUIRE_THAT(hero.getCurrentHealth(), Catch::Matchers::WithinRel(55, 1e-4));
}