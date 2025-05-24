#include "game/Game.hpp"

int main(int argc, char *argv[]) {
    Game game;
    if(argc > 1) {
        game = Game::loadFromFile(argv[1]);
    } else {
        game = Game(1);
    }
    game.start();

    return 0;
}
