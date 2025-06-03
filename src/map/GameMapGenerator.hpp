#ifndef FMI_COURSE_PROJECT_DND_GAMEMAPGENERATOR_HPP
#define FMI_COURSE_PROJECT_DND_GAMEMAPGENERATOR_HPP

#include <vector>

/**
 * @class GameMapGenerator
 * @ingroup Map
 * @brief Generates random maze-like game maps.
 *
 * Uses randomized depth-first search to carve out mazes, and ensures a valid path exists
 * between the entrance and the exit of the map. Uses the algorithm described here: https://www.bo-song.com/how-to-generate-a-maze-with-c/
 */
class GameMapGenerator {
public:
    /**
     * @brief Constructs a new GameMapGenerator instance.
     * @param height The height of the map.
     * @param width The width of the map.
     */
    GameMapGenerator(size_t height, size_t width);

    /**
     * @brief Generates a randomized maze with a guaranteed valid path from entrance to exit.
     * @return A 2D vector representing the maze (' ' = path, '*' = wall).
     */
    std::vector<std::vector<char>> generateRandomMap();

private:
    size_t height;                         ///< Height of the maze.
    size_t width;                          ///< Width of the maze.
    std::vector<std::vector<char>> maze;   ///< 2D grid representing the maze layout.

    /**
     * @brief Recursive depth-first search to carve out the maze.
     * @param i Current row index.
     * @param j Current column index.
     */
    void dfs(int i, int j);

    /**
     * @brief Counts the number of adjacent visited path cells.
     * @param i Row index to check.
     * @param j Column index to check.
     * @return Number of neighboring path cells.
     */
    int countVisitedNeighbors(int i, int j) const;

    /**
     * @brief Checks if the goal cell is reachable from the start using DFS.
     * @param goalX Goal X position.
     * @param goalY Goal Y position.
     * @return True if a path exists from start to goal.
     */
    bool isReachable(int goalX, int goalY) const;

    /**
     * @brief Forces a direct path to the exit if one doesn't already exist.
     * @param goalX Goal cell row.
     * @param goalY Goal cell column.
     */
    void forcePathToExit(int goalX, int goalY);
};

#endif
