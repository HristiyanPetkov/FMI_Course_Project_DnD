#include <catch2/catch_all.hpp>
#include "../character/Character.hpp"
#include "../item/Armor.hpp"
#include "../item/Weapon.hpp"
#include "../item/Spell.hpp"

TEST_CASE("Character initialization", "[Character]") {
    SECTION("Human stats are correct") {
        Character human("Bob", CharacterClass::Human);
        std::ostringstream oss;
        human.print(oss);
        std::string output = oss.str();
        REQUIRE(output.find("Strength: 45") != std::string::npos);
        REQUIRE(output.find("Mana: 30") != std::string::npos);
        REQUIRE(human.getCurrentHealth() == 80);
    }

    SECTION("Mage stats are correct") {
        Character mage("Gandalf", CharacterClass::Mage);
        std::ostringstream oss;
        mage.print(oss);
        std::string output = oss.str();
        REQUIRE(output.find("Strength: 25") != std::string::npos);
        REQUIRE(output.find("Mana: 70") != std::string::npos);
        REQUIRE(mage.getCurrentHealth() == 100);
    }

    SECTION("Warrior stats are correct") {
        Character warrior("Conan", CharacterClass::Warrior);
        std::ostringstream oss;
        warrior.print(oss);
        std::string output = oss.str();
        REQUIRE(output.find("Strength: 60") != std::string::npos);
        REQUIRE(output.find("Mana: 25") != std::string::npos);
        REQUIRE(warrior.getCurrentHealth() == 120);
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
        REQUIRE(char1.getCurrentHealth() == 40);
    }

    SECTION("Heal above 50% increases by 20%") {
        char1.takeDamage(30.0);
        char1.heal();
        REQUIRE(char1.getCurrentHealth() == 66);
    }

    SECTION("Overheal results in maxHealth") {
        char1.heal();
        std::ostringstream oss;
        char1.print(oss);
        std::string output = oss.str();
        REQUIRE(char1.getCurrentHealth() == 80);
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

TEST_CASE("Character equips new items", "[Character]") {
    Character character("Hero", CharacterClass::Human);

    SECTION("Character equips new Armor") {
        Item* armor = new Armor("Leather Armor", 50);
        character.equipItem(armor, ItemType::ARMOR);
        character.takeDamage(20);
        std::ostringstream oss;
        character.print(oss);
        std::string output = oss.str();
        REQUIRE(output.find("Leather Armor 50") != std::string::npos);
        REQUIRE(character.getCurrentHealth() == 70);

        delete armor;
    }

    SECTION("Character equips new Weapon") {
        Item* weapon = new Weapon("Steel Sword", 50);
        character.equipItem(weapon, ItemType::WEAPON);
        std::ostringstream oss;
        character.print(oss);
        std::string output = oss.str();
        REQUIRE(output.find("Steel Sword 50") != std::string::npos);

        delete weapon;
    }

    SECTION("Character equips new Spell") {
        Item* spell = new Spell("Ice Spear", 50);
        character.equipItem(spell, ItemType::SPELL);
        std::ostringstream oss;
        character.print(oss);
        std::string output = oss.str();
        REQUIRE(output.find("Ice Spear 50") != std::string::npos);

        delete spell;
    }
}
