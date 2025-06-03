#include <functional>
#include <ctime>
#include <stack>
#include <random>
#include "GameMapGenerator.hpp"

GameMapGenerator::GameMapGenerator(size_t height, size_t width)
        : height(height), width(width), maze(height, std::vector<char>(width, '*')) {}

std::vector<std::vector<char>> GameMapGenerator::generateRandomMap() {
    std::srand(std::time(nullptr));
    dfs(1, 1);

    if (!isReachable(height - 2, width - 2)) {
        forcePathToExit(height - 2, width - 2);
    }

    return maze;
}

void GameMapGenerator::dfs(int i, int j) {
    static int dir[4][2] = { {0,1}, {0,-1}, {-1,0}, {1,0} };
    int order[] = {0, 1, 2, 3};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(order, order + 4, gen);

    if (i < 1 || j < 1 || i > height - 2 || j > width - 2) return;
    if (maze[i][j] == ' ') return;
    if (countVisitedNeighbors(i, j) > 1) return;

    maze[i][j] = ' ';

    for (int k = 0; k < 4; ++k) {
        int ni = i + dir[order[k]][0];
        int nj = j + dir[order[k]][1];
        dfs(ni, nj);
    }
}

int GameMapGenerator::countVisitedNeighbors(int i, int j) const {
    static int dir[4][2] = {{0,1}, {0,-1}, {-1,0}, {1,0}};
    int count = 0;
    for (auto& d : dir) {
        int ni = i + d[0], nj = j + d[1];
        if (ni >= 0 && nj >= 0 && ni < height && nj < width && maze[ni][nj] == ' ')
            count++;
    }
    return count;
}

bool GameMapGenerator::isReachable(int goalX, int goalY) const {
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
    std::stack<std::pair<int, int>> stack;
    stack.push({1, 1});

    static int dir[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};

    while (!stack.empty()) {
        auto [x, y] = stack.top();
        stack.pop();

        if (x == goalX && y == goalY) return true;

        visited[x][y] = true;

        for (auto& d : dir) {
            int ni = x + d[0], nj = y + d[1];
            if (ni >= 0 && nj >= 0 && ni < height && nj < width &&
                maze[ni][nj] == ' ' && !visited[ni][nj]) {
                stack.push({ni, nj});
            }
        }
    }

    return false;
}

void GameMapGenerator::forcePathToExit(int goalX, int goalY) {
    int x = 1, y = 1;
    while (x != goalX || y != goalY) {
        maze[x][y] = ' ';
        if (x < goalX) x++;
        else if (x > goalX) x--;
        else if (y < goalY) y++;
        else if (y > goalY) y--;
    }
    maze[goalX][goalY] = ' ';
}
