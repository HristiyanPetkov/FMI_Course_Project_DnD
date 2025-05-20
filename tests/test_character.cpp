#include <catch2/catch_all.hpp>
#include "../character/Character.hpp"

TEST_CASE("Character initialization", "[Character]") {
    SECTION("Human stats are correct") {
        Character human("Bob", CharacterClass::Human);
        std::ostringstream oss;
        human.print(oss);
        std::string output = oss.str();
        REQUIRE(output.find("Strength: 30") != std::string::npos);
        REQUIRE(output.find("Mana: 20") != std::string::npos);
        REQUIRE(output.find("Health: 50") != std::string::npos);
    }

    SECTION("Mage stats are correct") {
        Character mage("Gandalf", CharacterClass::Mage);
        std::ostringstream oss;
        mage.print(oss);
        std::string output = oss.str();
        REQUIRE(output.find("Strength: 10") != std::string::npos);
        REQUIRE(output.find("Mana: 40") != std::string::npos);
    }

    SECTION("Warrior stats are correct") {
        Character warrior("Conan", CharacterClass::Warrior);
        std::ostringstream oss;
        warrior.print(oss);
        std::string output = oss.str();
        REQUIRE(output.find("Strength: 40") != std::string::npos);
        REQUIRE(output.find("Mana: 10") != std::string::npos);
    }
}

TEST_CASE("Character can die", "[Character]") {
    Character testChar("Test", CharacterClass::Human);
    testChar.takeDamage(100.0);

    REQUIRE(testChar.isAlive() == false);
}

TEST_CASE("Character heals correctly", "[Character]") {
    Character char1("Healer", CharacterClass::Human);

    SECTION("Heal below 50% health brings to 50%") {
        char1.takeDamage(45.0);
        char1.heal();
        std::ostringstream oss;
        char1.print(oss);
        std::string output = oss.str();
        REQUIRE(output.find("Health: 25") != std::string::npos);
    }

    SECTION("Heal above 50% increases by 20%") {
        char1.takeDamage(10.0); // 40 HP
        char1.heal(); // +10 (20%)
        std::ostringstream oss;
        char1.print(oss);
        std::string output = oss.str();
        REQUIRE(output.find("Health: 50") != std::string::npos);
    }
}

TEST_CASE("Character copy constructor and assignment operator", "[Character]") {
    Character original("Hero", CharacterClass::Warrior);
    original.takeDamage(20.0);

    SECTION("Copy constructor creates equivalent but independent object") {
        Character copy(original);
        std::ostringstream ossOriginal, ossCopy;
        original.print(ossOriginal);
        copy.print(ossCopy);
        REQUIRE(ossOriginal.str() == ossCopy.str());
    }

    SECTION("Assignment operator creates equivalent but independent object") {
        Character copy("Temp", CharacterClass::Mage);
        copy = original;

        std::ostringstream ossOriginal, ossCopy;
        original.print(ossOriginal);
        copy.print(ossCopy);
        REQUIRE(ossOriginal.str() == ossCopy.str());
    }
}
