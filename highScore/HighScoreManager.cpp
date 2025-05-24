#include <fstream>
#include <vector>
#include <sstream>
#include "HighScoreManager.hpp"

const std::string HighScoreManager::highScorePath = "highScores.txt";

void HighScoreManager::saveScore(unsigned int level, const Character &player) {
    std::fstream file(HighScoreManager::highScorePath, std::ios::in);
    std::vector<Score> scores;
    Score currentScore(level, player);

    if(file) {
        std::string line;
        while(getline(file, line)) {
            Score highScore;
            std::istringstream lineStream(line);
            lineStream >> highScore.level;
            highScore.player.deserializeForHighScore(lineStream);
            scores.push_back(highScore);
        }
        file.close();
    }

    auto it = std::find_if(scores.begin(), scores.end(), [&](const Score& hs) {
        if(currentScore.level > hs.level) {
            return true;
        } else if(currentScore.level == hs.level && currentScore.player < hs.player) {
            return true;
        }
        return false;
    });
    scores.insert(it, currentScore);

    file.open(HighScoreManager::highScorePath, std::ios::out);
    for (const auto& hs : scores) {
        file << hs.level << " ";
        hs.player.serializeForHighScore(file);
    }
}