#ifndef Game_hpp
#define Game_hpp

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<string>
#include <stdio.h>

class Game {
public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int h, int w, bool fullscreen);

    void handleEvent();

    void update();

    void render();
    
    void clean();

    bool running();

    int cnt;

    static bool firstCheck;
    static SDL_Renderer *gRenderer;
    static SDL_Rect gCamera;


private: 

    bool isRunning;
    SDL_Window *gWindow;

};
#endif