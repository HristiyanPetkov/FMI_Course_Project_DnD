cmake_minimum_required(VERSION 3.22)
project(FMI_Course_Project_DnD)

set(CMAKE_CXX_STANDARD 20)

add_library(DnD STATIC)
target_sources(
        DnD
        PRIVATE
            character/Character.cpp
            character/Character.hpp
            character/CharacterFactory.cpp
            character/CharacterFactory.hpp
            character/CharacterClass.cpp
            character/CharacterClass.hpp
            item/Item.cpp
            item/Item.hpp
            item/Armor.cpp
            item/Armor.hpp
            item/Weapon.cpp
            item/Weapon.hpp
            item/Spell.cpp
            item/Spell.hpp
            item/ItemType.cpp
            item/ItemType.hpp
            monster/Monster.cpp
            monster/Monster.hpp
            battle/BattleSystem.cpp
            battle/BattleSystem.hpp
            map/GameMap.cpp
            map/GameMap.hpp
            map/Direction.cpp
            map/Direction.hpp
            map/tile/Tile.cpp
            map/tile/Tile.hpp
            map/tile/CharacterTile.cpp
            map/tile/CharacterTile.hpp
            map/tile/MonsterTile.cpp
            map/tile/MonsterTile.hpp
            map/tile/TreasureTile.cpp
            map/tile/TreasureTile.hpp
            map/tile/EmptyTile.cpp
            map/tile/EmptyTile.hpp
            map/tile/WallTile.cpp
            map/tile/WallTile.hpp
            map/GameMapFactory.cpp
            map/GameMapFactory.hpp
            game/Game.cpp
            game/Game.hpp
            game/InputCommand.cpp
            game/InputCommand.hpp
)

add_executable(DnD_application)
target_sources(
        DnD_application
        PRIVATE
            main.cpp
)
target_link_libraries(
        DnD_application
        PRIVATE
            DnD
)

include(CTest)
include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY "https://github.com/catchorg/Catch2.git"
        GIT_TAG        v3.4.0
)

FetchContent_MakeAvailable(Catch2)
include(Catch)

add_executable(test_runner)
target_link_libraries(
        test_runner
        PRIVATE
            DnD
            Catch2::Catch2WithMain
)
target_sources(
        test_runner
        PRIVATE
            tests/test_character.cpp
            tests/test_item.cpp
            tests/test_monster.cpp
            tests/test_character_monster_interactions.cpp
)
catch_discover_tests(test_runner)