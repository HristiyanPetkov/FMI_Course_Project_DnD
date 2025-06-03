#ifndef FMI_COURSE_PROJECT_DND_HIGHSCOREMANAGER_HPP
#define FMI_COURSE_PROJECT_DND_HIGHSCOREMANAGER_HPP

#include "../character/Character.hpp"

/**
 * @struct Score
 * @brief Represents a game score with associated player data.
 */
struct Score {
    unsigned level;     ///< The level reached by the player.
    Character player;   ///< The character data of the player.
};

/**
 * @class HighScoreManager
 * @brief Manages saving and retrieving high scores.
 */
class HighScoreManager {
public:
    static const std::string highScorePath; ///< File path to high scores.

    /**
     * @brief Saves a player's score.
     * @param level The level the player reached.
     * @param player The player's character.
     */
    static void saveScore(unsigned level, const Character& player);

    /**
     * @brief Displays the current high scores.
     * @param amount The amount of high scores to be printed in descending order. Default behaviour is top 10 scores.
     * @note If file has less then the desired amount of high scores, then the method output until EOF.
     */
    static void displayHighScores(int amount = 10);
};

#endif
