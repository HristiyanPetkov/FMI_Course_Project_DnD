#include <catch2/catch_all.hpp>
#include "../monster/Monster.hpp"
#include "../character/Character.hpp"

TEST_CASE("Monster initialization", "[Monster]") {
    double takenDamageMultForLevel10 = 15;
    for(size_t i = 0; i < 9; ++ i) {
        takenDamageMultForLevel10 += takenDamageMultForLevel10 * 0.05;
    }
    takenDamageMultForLevel10 = 1 - takenDamageMultForLevel10 / 100;


    SECTION("Monster stats are correct at level 1") {
        Monster dragon("Dragon", 1);
        std::ostringstream oss;
        dragon.print(oss);
        std::string output = oss.str();
        REQUIRE(output.find("Strength: 25") != std::string::npos);
        REQUIRE(output.find("Mana: 25") != std::string::npos);
        REQUIRE(dragon.getCurrentHealth() == 50);
        REQUIRE(output.find("Damage reduction mult: 0.85") != std::string::npos);
    }

    SECTION("Damage reduction mult is calculated correctly for level 10") {
        REQUIRE_THAT(Monster::getStartingTakenDamageMult(10), Catch::Matchers::WithinRel(takenDamageMultForLevel10, 1e-4));
    }

    SECTION("Monster stats are correct at level 10") {
        Monster dragon("Dragon", 10);
        std::ostringstream oss;
        dragon.print(oss);
        std::string output = oss.str();
        REQUIRE(output.find("Strength: 115") != std::string::npos);
        REQUIRE(output.find("Mana: 115") != std::string::npos);
        REQUIRE(dragon.getCurrentHealth() == 140);
        REQUIRE(output.find("Damage reduction mult: " + std::to_string(takenDamageMultForLevel10)) != std::string::npos);
    }

    SECTION("Damage reduction mult is calculated correctly for level 40") {
        REQUIRE(Monster::getStartingTakenDamageMult(40) == 0.01);
    }

    SECTION("Monster stats are correct at level 40") {
        Monster dragon("Dragon",  40);
        std::ostringstream oss;
        dragon.print(oss);
        std::string output = oss.str();
        REQUIRE(output.find("Strength: 415") != std::string::npos);
        REQUIRE(output.find("Mana: 415") != std::string::npos);
        REQUIRE(dragon.getCurrentHealth() == 440);
        REQUIRE(output.find("Damage reduction mult: 0.01") != std::string::npos);
    }
}

TEST_CASE("Monster can die", "[Monster]") {
    Monster dragon("Dragon", 1);
    dragon.takeDamage(60);
    REQUIRE(dragon.isAlive() == false);
}

TEST_CASE("Monster damage reduction scales with level", "[Monster]") {
    SECTION("Damage reduction at level 1 is 15%") {
        Monster dragon("Dragon", 1);
        dragon.takeDamage(50);
        REQUIRE_THAT(dragon.getCurrentHealth(), Catch::Matchers::WithinRel(7.5, 1e-4));
    }

    SECTION("Damage reduction at level 10 is ~24%") {
        Monster dragon("Dragon", 10);
        dragon.takeDamage(40);
        double takenDamageMultForLevel10 = 15;
        for(size_t i = 0; i < 9; ++ i) {
            takenDamageMultForLevel10 += takenDamageMultForLevel10 * 0.05;
        }
        takenDamageMultForLevel10 = 1 - takenDamageMultForLevel10 / 100;
        double expectedHealth = 140 - 40*takenDamageMultForLevel10;
        REQUIRE_THAT(dragon.getCurrentHealth(), Catch::Matchers::WithinRel(expectedHealth, 1e-4));
    }

    SECTION("Damage reduction at level 40 is 99%") {
        Monster dragon("Dragon", 40);
        dragon.takeDamage(100);
        REQUIRE_THAT(dragon.getCurrentHealth(), Catch::Matchers::WithinRel(439, 1e-4));
    }
}
