#ifndef FMI_COURSE_PROJECT_DND_GAME_HPP
#define FMI_COURSE_PROJECT_DND_GAME_HPP

#include "../map/GameMap.hpp"
#include "../character/Character.hpp"

/**
 * @defgroup Game
 * @brief Game management
 * @details Game class and console commands for the game loop
 */

/**
 * @enum GameDisplay
 * @ingroup Game
 * @brief Represents the rendering mode for the game.
 */
enum class GameDisplay {
    Terminal,   ///< Indicates terminal/console mode
    SFML        ///< Indicates graphical/SFML mode
};

/**
 * @class Game
 * @ingroup Game
 * @brief Manages the game lifecycle, including gameplay loop, state management, and rendering.
 */
class Game {
public:
    /**
     * @brief Default constructor. Initiates the game at level 0, in other words incomplete
     */
    Game();

    /**
     * @brief Constructs a game starting at a specified level.
     * @param level The initial level.
     */
    explicit Game(unsigned level);

    /**
     * @brief Constructs a game with a given character and starting level.
     * @param character The player character.
     * @param level The initial level (default is 1).
     */
    explicit Game(const Character& character, unsigned level = 1);

    /**
     * @brief Starts the game loop in terminal mode.
     */
    void start();

    /**
     * @brief Starts the game loop in graphical mode using SFML.
     * @param window The SFML render window.
     */
    void startSFML(sf::RenderWindow& window);

    /**
     * @brief Loads a saved game from a file.
     * @param filePath The path to the saved game file.
     * @return The loaded Game object.
     */
    static Game loadFromFile(const std::string& filePath);

private:
    unsigned level;          ///< Current game level.
    Character player;        ///< The player character.
    GameMap currentMap;      ///< The current game map.

    /**
     * @brief Saves the current game state to a file.
     * @param filePath The path where the game should be saved.
     */
    void save(const std::string& filePath);

    /**
     * @brief Updates the high scores.
     */
    void updateHighScores();

    /**
     * @brief Checks if the character is on the next level tile and progresses the level if so.
     */
    void checkForNextLevel();

    /**
     * @brief Renders the in-game menu using SFML.
     * @param window The SFML render window.
     */
    void visualizeMenu(sf::RenderWindow& window);
};

#endif
