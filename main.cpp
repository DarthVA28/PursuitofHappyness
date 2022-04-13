#include "Game.hpp"

Game *game = NULL;

int main(int argc, const char *argv[]) {

    const int FPS = 60;
    const int fDelay = 1000 / FPS;

    Uint32 fStart;
    int fTime; 
    
    game = new Game();

    game->init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

    while(game->running()) {
        game -> handleEvent();
        game -> update();
        game -> render();

        // fTime = SDL_GetTicks() - fStart;

        // if (fDelay > fTime) {
        //     SDL_Delay(fDelay-fTime);
        // }
    }

    return 0;
}