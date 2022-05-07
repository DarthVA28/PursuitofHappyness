#include "TM.hpp"

SDL_Texture* TM::LoadTexture(const char* texture) {
    SDL_Texture* ldtex = IMG_LoadTexture(Game::gRenderer, texture);
    return ldtex;
}

void TM::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest) {
    SDL_RenderCopy(Game::gRenderer, tex, &src, &dest);
}