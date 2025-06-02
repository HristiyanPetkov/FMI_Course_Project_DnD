cmake_minimum_required(VERSION 3.22)
project(FMI_Course_Project_DnD)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external/SFML)

add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources
)

add_library(DnD STATIC)
target_sources(
        DnD
        PRIVATE
        src/character/Character.cpp
        src/character/Character.hpp
        src/character/CharacterFactory.cpp
        src/character/CharacterFactory.hpp
        src/character/CharacterClass.cpp
        src/character/CharacterClass.hpp
        src/item/Item.cpp
        src/item/Item.hpp
        src/item/Armor.cpp
        src/item/Armor.hpp
        src/item/Weapon.cpp
        src/item/Weapon.hpp
        src/item/Spell.cpp
        src/item/Spell.hpp
        src/item/ItemType.cpp
        src/item/ItemType.hpp
        src/monster/Monster.cpp
        src/monster/Monster.hpp
        src/battle/BattleSystem.cpp
        src/battle/BattleSystem.hpp
        src/map/GameMap.cpp
        src/map/GameMap.hpp
        src/map/Direction.cpp
        src/map/Direction.hpp
        src/map/tile/Tile.cpp
        src/map/tile/Tile.hpp
        src/map/tile/CharacterTile.cpp
        src/map/tile/CharacterTile.hpp
        src/map/tile/MonsterTile.cpp
        src/map/tile/MonsterTile.hpp
        src/map/tile/TreasureTile.cpp
        src/map/tile/TreasureTile.hpp
        src/map/tile/EmptyTile.cpp
        src/map/tile/EmptyTile.hpp
        src/map/tile/WallTile.cpp
        src/map/tile/WallTile.hpp
        src/map/GameMapFactory.cpp
        src/map/GameMapFactory.hpp
        src/game/Game.cpp
        src/game/Game.hpp
        src/game/InputCommand.cpp
        src/game/InputCommand.hpp
        src/highScore/HighScoreManager.cpp
        src/highScore/HighScoreManager.hpp
)

target_link_libraries(
        DnD
        PUBLIC
            sfml-graphics
            sfml-window
            sfml-system
)

add_dependencies(DnD copy_assets)


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

get_target_property(SFML_INCLUDE_DIRS sfml-graphics INTERFACE_INCLUDE_DIRECTORIES)
message("SFML include dirs (evaluated): ${SFML_INCLUDE_DIRS}")

target_include_directories(DnD_application
        PRIVATE
        ${SFML_INCLUDE_DIRS}
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