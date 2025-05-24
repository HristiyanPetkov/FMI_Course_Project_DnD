#ifndef FMI_COURSE_PROJECT_DND_HIGHSCOREMANAGER_HPP
#define FMI_COURSE_PROJECT_DND_HIGHSCOREMANAGER_HPP

#include "../character/Character.hpp"

struct Score {
    unsigned level;
    Character player;
};

class HighScoreManager {
public:
    static const std::string highScorePath;
    static void saveScore(unsigned level, const Character& player);
};

#endif
