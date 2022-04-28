#include "Game.hpp"
#include "TM.hpp"
#include "Object.hpp"
#include "Map.hpp"
#include "Tuple.hpp"

SDL_Rect srcR, destR;

enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

Object* player;
Object* player2;
Map* map;

SDL_Rect Game::gCamera = {0,0,800,600};
SDL_Renderer* Game::gRenderer = nullptr;

Game::Game() {}

Game::~Game() {}

void Game::init(const char* win_title, int xpos, int ypos, int h, int w, bool fs) {
    //Initialization flag
	bool success = true;
    int flags = 0;
    cnt = w-128;
    if (fs) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

	//Initialize SDL
	if( SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow(win_title, xpos, ypos, h, w, flags);
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
            // gScreenSurface = SDL_GetWindowSurface( gWindow );
			gRenderer = SDL_CreateRenderer(gWindow,-1,0);
			if  (gRenderer == NULL) {
					printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );
					success = false;
			} else {
                SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
            }

		}
	}

    if (success) {
        isRunning = true;
    } else {
        isRunning = false;
    }

    player = new Object("assets/p1.png", 12376,2048);
    player2 = new Object("assets/p2.png", 128,128);
    map = new Map(); 
}

void Game::handleEvent()  {
    SDL_Event e; 
    SDL_PollEvent(&e);

    switch(e.type) {
        case SDL_QUIT:
        {
            isRunning = false;
            break;
        }

        case SDL_KEYDOWN:
        {
            SDL_Rect b = (player2->getCollider());
            switch( e.key.keysym.sym ) {
                case SDLK_UP:
                    player->objMove(KEY_PRESS_SURFACE_UP,b,map->Colliders);
                    break;

                case SDLK_DOWN:
                    player->objMove(KEY_PRESS_SURFACE_DOWN,b,map->Colliders);
                    break;

                case SDLK_LEFT:
                    player->objMove(KEY_PRESS_SURFACE_LEFT,b,map->Colliders);
                    break;

                case SDLK_RIGHT:
                    player->objMove(KEY_PRESS_SURFACE_RIGHT,b,map->Colliders);
                    break;

                default:
                break;
            }
            break; 
        }

        default:
            break;
    }
}

void Game::update() {
    player->objUpdate();
    player2->objUpdate();

    gCamera.x = (player->getx()-400);
    gCamera.y = (player->gety()-300);

    // if( gCamera.x < 0 ) { 
    //     gCamera.x = 0;
    // }
    // if( gCamera.y < 0 ) {
    //     gCamera.y = 0;
    // }
    // if( gCamera.x > 32*(map->MAP_X) - gCamera.w ){
    //     gCamera.x = (map->MAP_X) - gCamera.w;
    // }
    // if( gCamera.y > 32*(map->MAP_Y) - gCamera.h ) {
    //     gCamera.y = (map->MAP_Y) - gCamera.h;
    // }

}

void Game::render() {
    SDL_RenderClear(gRenderer);
    map->DrawMap(gCamera.x, gCamera.y);
    player->objRender(gCamera.x, gCamera.y);
    // player->objRender();
    player2->objRender(gCamera.x, gCamera.y);
    SDL_RenderPresent(gRenderer);
}

void Game::clean() {
    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(gRenderer);
    SDL_Quit();
    }

bool Game::running() {
    if (isRunning) {
        return true;
    } else {
        return false;
    }
}