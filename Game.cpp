#include "Game.hpp"
#include "TM.hpp"
#include "Object.hpp"
#include "Map.hpp"
#include "NPC.hpp"
#include "Tuple.hpp"
// #include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <sstream>

using std::string;

// Mix_Music *gMusic = nullptr;

// //The sound effects that will be used
// Mix_Chunk *gScratch = NULL;
// Mix_Chunk *gHigh = NULL;
// Mix_Chunk *gMedium = NULL;
// Mix_Chunk *gLow = NULL;

// Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

unsigned int tinit,t1,t2,t3,t4;
std::stringstream timeText;
Uint32 startTime = 0;
string display = "TRAVELLING...";
string hunger = "00";
string money = "00";
string taskDone = "00";

// Button constants
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 1;

bool firstScreen = true;
bool musicOn = true;
bool play = true;
bool openInventory = false;
bool openTaskSchedule = false;
bool openMenu1 = false;
bool openMenu2 = false;
bool loc1eat = false;
bool loc2eat = false;
bool Game ::firstCheck = true;
SDL_Renderer *Game::gRenderer = nullptr;

int posIndex = 0;
Tuple* posArray[20];

// for text
TTF_Font *gFont = NULL;
TTF_Font *gFont1 = NULL;

enum LButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_TOTAL = 4
};
enum musicSprite
{
	musicOnSpriteV = 0,
	musicOffSpriteV = 1,

	BUTTON_SPRITE_TOTALS = 2
};

// Texture wrapper class
class LTexture
{
public:
	// Initializes variables
	LTexture();

	// Deallocates memory
	~LTexture();

	// Loads image at specified path
	bool loadFromFile(std::string path);
	SDL_Texture *loadFromFile1(std::string path);

#if defined(SDL_TTF_MAJOR_VERSION)
	// Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
	bool loadFromRenderedText1(std::string textureText, SDL_Color textColor);
#endif

	// Deallocates texture
	void free();

	// Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	// Set blending
	void setBlendMode(SDL_BlendMode blending);

	// Set alpha modulation
	void setAlpha(Uint8 alpha);

	// Renders texture at given point
	void render(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// Gets image dimensions
	int getWidth();
	int getHeight();

private:
	// The actual hardware texture
	SDL_Texture *mTexture;

	// Image dimensions
	int mWidth;
	int mHeight;
};

// The mouse button
class LButton
{
public:
	// Initializes internal variables
	LButton();

	// Sets top left position
	void setPosition(int x, int y, int length, int height);

	// Handles mouse event
	void handleEvent(SDL_Event *e);

	// Shows button sprite
	void renderStart();
	void renderMusic();

private:
	// Top left position
	SDL_Point mPosition;
	int mlength;
	int mheight;
	// Currently used global sprite
	LButtonSprite mCurrentSprite;
	musicSprite mmusicSprite;
};

// Mouse button sprites
SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL];
SDL_Rect musicOffSprite;
SDL_Rect musicOnSprite;
SDL_Rect musicOffSpritedest;
SDL_Rect musicOnSpritedest;
LTexture gButtonSpriteSheetTexture;
LTexture pauseSpriteSheetTexture;
LTexture playSpriteSheetTexture;
LTexture musicOnSpriteSheetTexture;
LTexture musicOffSpriteSheetTexture;
LTexture gTimeTextTexture;

// Buttons objects
LButton gButtons[TOTAL_BUTTONS];
LButton musicOnButton;
LButton musicOffButton;

LTexture::LTexture()
{
	// Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	// Deallocate
	free();
}
LTexture gbtexture1;
bool LTexture::loadFromFile(std::string path)
{
	// Get rid of preexisting texture
	free();

	// The final texture
	SDL_Texture *newTexture = NULL;

	// Load image at specified path
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		// Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(Game::gRenderer, loadedSurface);

		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			// Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	// Return success
	mTexture = newTexture;
	return mTexture != NULL;
}
SDL_Texture *LTexture::loadFromFile1(std::string path)
{
	// Get rid of preexisting texture
	free();

	// The final texture
	SDL_Texture *newTexture = NULL;

	// Load image at specified path
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		// Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(Game::gRenderer, loadedSurface);

		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			// Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	// Return success
	mTexture = newTexture;
	return mTexture;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	// Get rid of preexisting texture
	free();

	// Render text surface
	SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		// Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(Game::gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			// Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		// Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	// Return success
	return mTexture != NULL;
}

bool LTexture::loadFromRenderedText1(std::string textureText, SDL_Color textColor)
{
	// Get rid of preexisting texture
	free();

	// Render text surface
	SDL_Surface *textSurface1 = TTF_RenderText_Solid(gFont1, textureText.c_str(), textColor);
	if (textSurface1 == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		// Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(Game::gRenderer, textSurface1);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			// Get image dimensions
			mWidth = textSurface1->w;
			mHeight = textSurface1->h;
		}

		// Get rid of old surface
		SDL_FreeSurface(textSurface1);
	}

	// Return success
	return mTexture != NULL;
}

#endif

void LTexture::free()
{
	// Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	// Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	// Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	// Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
	// Set rendering space and render to screen
	SDL_Rect renderQuad = {x, y, mWidth, mHeight};

	// Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	// Render to screen
	SDL_RenderCopyEx(Game::gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;
	mlength = 0;
	mheight = 0;
	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
	mmusicSprite = musicOnSpriteV;
}

void LButton::setPosition(int x, int y, int length, int height)
{
	mPosition.x = x;
	mPosition.y = y;
	mlength = length;
	mheight = height;
}

void LButton::handleEvent(SDL_Event *e)
{
	// If mouse event happened
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		// Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		// Check if mouse is in button
		bool inside = true;

		// Mouse is left of the button
		if (x < mPosition.x)
		{
			inside = false;
		}
		// Mouse is right of the button
		else if (x > mPosition.x + mlength)
		{
			inside = false;
		}
		// Mouse above the button
		else if (y < mPosition.y)
		{
			inside = false;
		}
		// Mouse below the button
		else if (y > mPosition.y + mheight)
		{
			inside = false;
		}

		// Mouse is outside button
		if (!inside)
		{
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		// Mouse is inside button
		else
		{
			// Set mouse over sprite
			switch (e->type)
			{
			case SDL_MOUSEMOTION:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;

			case SDL_MOUSEBUTTONDOWN:

				mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
				firstScreen = false;
				Game ::firstCheck = false;
				// if(musicOn)
				// {
				// printf("1");
				// mmusicSprite = musicOffSpriteV;
				// musicOn = false;
				// }
				// if(!musicOn)
				// {
				// mmusicSprite = musicOnSpriteV;
				// musicOn = true;
				// }
				break;

			case SDL_MOUSEBUTTONUP:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
				break;
			}
		}
	}
}

void LButton::renderStart()
{
	// Show current button sprite
	gButtonSpriteSheetTexture.render(mPosition.x, mPosition.y, &gSpriteClips[mCurrentSprite]);
}
void LButton::renderMusic()
{
	if (musicOn)

	{
		SDL_RenderCopyEx(Game::gRenderer, musicOnSpriteSheetTexture.loadFromFile1("assets/musicOn.png"), &musicOnSprite, &musicOnSpritedest, 0.0, NULL, SDL_FLIP_NONE);
	}
	if (!musicOn)

	{
		SDL_RenderCopyEx(Game::gRenderer, musicOffSpriteSheetTexture.loadFromFile1("assets/musicOff.png"), &musicOffSprite, &musicOffSpritedest, 0.0, NULL, SDL_FLIP_NONE);
	}
}
/*	if(play)
	{
		playSpriteSheetTexture.render( mPosition.x, mPosition.y, &gSpriteClips[ mCurrentSprite ] );
	}
	if(!play)
	{
		pauseSpriteSheetTexture.render( mPosition.x, mPosition.y, &gSpriteClips[ mCurrentSprite ] );
	} */

//------------------------------------------------------------------------------- MUSIC---------------------------------------------------------------------------------------------
LTexture gPromptTexture;

// bool loadMusicMedia()
// {
// 	//Loading success flag
// 	bool success = true;

// 	//Load prompt texture

// 	//Load music
// 	gMusic = Mix_LoadMUS( "assets/beat.wav" );
// 	if( gMusic == NULL )
// 	{
// 		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
// 		success = false;
// 	}

// 	//Load sound effects
// 	gScratch = Mix_LoadWAV( "assets/scratch.wav" );
// 	if( gScratch == NULL )
// 	{
// 		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
// 		success = false;
// 	}

// 	gHigh = Mix_LoadWAV( "assets/high.wav" );
// 	if( gHigh == NULL )
// 	{
// 		printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
// 		success = false;
// 	}

// 	gMedium = Mix_LoadWAV( "assets/medium.wav" );
// 	if( gMedium == NULL )
// 	{
// 		printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
// 		success = false;
// 	}

// 	gLow = Mix_LoadWAV( "assets/low.wav" );
// 	if( gLow == NULL )
// 	{
// 		printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
// 		success = false;
// 	}

// 	return success;

// }

/*void musicClose()
{
	//Free loaded images
	gPromptTexture.free();

	//Free the sound effects
	Mix_FreeChunk( gScratch );
	Mix_FreeChunk( gHigh );
	Mix_FreeChunk( gMedium );
	Mix_FreeChunk( gLow );
	gScratch = NULL;
	gHigh = NULL;
	gMedium = NULL;
	gLow = NULL;

	//Free the music
	Mix_FreeMusic( gMusic );
	gMusic = NULL;

	//Destroy window
	SDL_DestroyRenderer( Game::gRenderer );
	SDL_DestroyWindow( Game::gWindow );
	//gWindow = NULL;
	//gRenderer = NULL;

	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
} */
//-----------------------------------TEXT AT TASK BAR ---------------------------------------
// Globally used font

// Rendered texture
LTexture gTextTexture;
LTexture gHungerTexture;
LTexture gMoneyTexture;
LTexture gTaskCompletedTexture;
bool loadTextMedia()
{
	// Loading success flag
	bool success = true;

	// Render text
	SDL_Color textColor = {0, 0, 0};
	if (!gTextTexture.loadFromRenderedText(display, textColor))
	{
		printf("Failed to render text texture!\n");
		success = false;
	}
	if (!gHungerTexture.loadFromRenderedText1("HUNGER: " + hunger, textColor))
	{
		printf("Failed to render text texture!\n");
		success = false;
	}if (!gMoneyTexture.loadFromRenderedText1("MONEY: "+ money, textColor))
	{
		printf("Failed to render text texture!\n");
		success = false;
	}if (!gTaskCompletedTexture.loadFromRenderedText1("TASKS DONE: " + taskDone, textColor))
	{
		printf("Failed to render text texture!\n");
		success = false;
	}

	return success;
}

//-----------------------------------START SCREEN---------------------------------------------
bool loadMedia()
{
	// Loading success flag
	bool success = true;

	// Load sprites
	if (!gbtexture1.loadFromFile("assets/button.png"))
	{
		printf("Failed to load button sprite texture!\n");
		success = false;
	}
	else if (!gButtonSpriteSheetTexture.loadFromFile("assets/button.png"))
	{
		printf("Failed to load button sprite texture!\n");
		success = false;
	}
	else if (!pauseSpriteSheetTexture.loadFromFile("assets/button.png"))
	{
		printf("Failed to load button sprite texture!\n");
		success = false;
	}
	else if (!playSpriteSheetTexture.loadFromFile("assets/button.png"))
	{
		printf("Failed to load button sprite texture!\n");
		success = false;
	}
	else if (!musicOnSpriteSheetTexture.loadFromFile("assets/musicOn.png"))
	{
		printf("Failed to load button sprite texture!\n");
		success = false;
	}
	else if (!musicOffSpriteSheetTexture.loadFromFile("assets/musicOff.png"))
	{
		printf("Failed to load button sprite texture!\n");
		success = false;
	}
	else
	{
		// Set sprites
		for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i)
		{
			gSpriteClips[i].x = 0;
			gSpriteClips[i].y = i * 200;
			gSpriteClips[i].w = BUTTON_WIDTH;
			gSpriteClips[i].h = BUTTON_HEIGHT;
		}

		// Set buttons in corners
		gButtons[0].setPosition(300, 350, BUTTON_WIDTH, BUTTON_HEIGHT);

		musicOnSprite.x = 0;
		musicOnSprite.y = 0;
		musicOnSprite.w = 381;
		musicOnSprite.h = 365;
		musicOffSprite.x = 0;
		musicOffSprite.y = 0;
		musicOffSprite.w = 367;
		musicOffSprite.h = 362;
		musicOnSpritedest.x = 700;
		musicOnSpritedest.y = 530;
		musicOnSpritedest.w = 50;
		musicOnSpritedest.h = 50;
		musicOffSpritedest.x = 700;
		musicOffSpritedest.y = 530;
		musicOffSpritedest.w = 50;
		musicOffSpritedest.h = 50;
		musicOnButton.setPosition(700, 530, 50, 50);
		musicOffButton.setPosition(700, 530, 50, 50);
	}

	return success;
}

/*void close()
{
	//Free loaded images
	gButtonSpriteSheetTexture.free();

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
} */

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

Object *player;
Object *player2;
NPC* activeNPC[10];
NPC *professor;
Map *map;

int NUM_ACTIVE_NPC = 0;

SDL_Rect Game::gCamera = {0, 0, 800, 600};

Game::Game() {}

Game::~Game() {}

void Game::init(const char *win_title, int xpos, int ypos, int h, int w, bool fs)
{
	// Initialization flag
	bool success = true;
	int flags = 0;
	cnt = w - 128;
	tinit = SDL_GetTicks();
	if (fs)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}

	else
	{ //Create window
		gWindow = SDL_CreateWindow(win_title, xpos, ypos, h, w, flags);
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			// Get window surface
			//  gScreenSurface = SDL_GetWindowSurface( gWindow );
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
				success = false;
			}
			// Initialize SDL_mixer
			// if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
			// {
			// 	printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
			// 	success = false;
			// }

			else
			{
				if (!loadMedia())
				{
					printf("Failed to load media!\n");
				}
				// if( !loadMusicMedia() )
				// {
				// 	printf( "Failed to load music media!\n" );
				// }

				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				// if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				// {
				//     printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
				//     success = false;
				// }
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}

				gFont = TTF_OpenFont("assets/lazy.ttf", 28);
				gFont1 = TTF_OpenFont("assets/lazy.ttf", 22);
				if (gFont == NULL)
				{
					printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
				}
				if (gFont1 == NULL)
				{
					printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
				}

				if (!loadTextMedia())
				{
					printf("Failed to load text media for taskbar!\n");
				}
			}
		}
	}

	if (success)
	{
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	player = new Object("assets/player.png", 12376, 2048);
	player2 = new Object("assets/player2.png", 12312, 2048);
	professor = new NPC("assets/prof.png", 12350, 1950,"PROF");
	activeNPC[0] = professor;
	NUM_ACTIVE_NPC ++;
	
	map = new Map();
	player->addItems("item1");
	player->addItems("item4");

	posArray[0] = new Tuple(12504,5248);
	posArray[1] = new Tuple(9032,4272);
	posArray[2] = new Tuple(12504,2880);
	posArray[3] = new Tuple(5652, 4432);
	posArray[4] = new Tuple(11472, 4412);
	posArray[5] = new Tuple(3072, 6932);
	posArray[6] = new Tuple(7352, 3132);
	posArray[7] = new Tuple(10112, 3572);
	posArray[8] = new Tuple(10572, 952);
	posArray[9] = new Tuple(12412, 4632);
	posArray[10] = new Tuple(5472, 6872);
	posArray[11] = new Tuple(12504,5248);
	posArray[12] = new Tuple(11552, 4632);
	posArray[13] = new Tuple(7312, 3832);
	posArray[14] = new Tuple(6072, 4492);
	posArray[15] = new Tuple(7172, 3852);
	posArray[16] = new Tuple(5332, 3632);
	posArray[17] = new Tuple(5372, 1852);
	posArray[18] = new Tuple(6572, 4592);
	posArray[19] = new Tuple(8372, 3132);
	t3 = SDL_GetTicks();
}

void Game::handleEvent()
{
	SDL_Event e;
	SDL_PollEvent(&e);

	bool quit = false;
	while (!quit && firstScreen)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			// User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				// switch (e.key.keysym.sym)
				// { // Play high sound effect
				// case SDLK_1:
				// 	Mix_PlayChannel(-1, gHigh, 0);
				// 	break;

				// // Play medium sound effect
				// case SDLK_2:
				// 	Mix_PlayChannel(-1, gMedium, 0);
				// 	break;
				// case SDLK_9:
				// 	// If there is no music playing
				// 	if (Mix_PlayingMusic() == 0)
				// 	{
				// 		// Play the music
				// 		Mix_PlayMusic(gMusic, -1);
				// 	}
				// 	// If music is being played
				// 	else
				// 	{
				// 		// If the music is paused
				// 		if (Mix_PausedMusic() == 1)
				// 		{
				// 			// Resume the music
				// 			Mix_ResumeMusic();
				// 		}
				// 		// If the music is playing
				// 		else
				// 		{
				// 			// Pause the music
				// 			Mix_PauseMusic();
				// 		}
				// 	}
				// 	break;

				// case SDLK_0:
				// 	// Stop the music
				// 	Mix_HaltMusic();
				// 	break;
				// }
			}

			// Handle button events
			for (int i = 0; i < TOTAL_BUTTONS; ++i)
			{
				gButtons[i].handleEvent(&e);
			}
		}

		// Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

		SDL_RenderClear(gRenderer);

		SDL_Rect cm = {0, 0, 50, 50};
		gbtexture1.render(40, 40, &cm);
		gPromptTexture.render(0, 0);
		// Render buttons
		for (int i = 0; i < TOTAL_BUTTONS; ++i)
		{
			gButtons[i].renderStart();
		}

		// Update screen
		SDL_RenderPresent(gRenderer);
	}

	SDL_Color textColor1 = {255, 0, 0};
	timeText.str( "" );
	timeText <<  SDL_GetTicks() -startTime ; 
	string temp = timeText.str();
	int temp1 = std::stoi(temp)/1000;
	string temp2 = std::to_string(temp1);
	if( !gTimeTextTexture.loadFromRenderedText( temp2.c_str(), textColor1 ) )
			{
				printf( "Unable to render time texture!\n" );
			}

	switch (e.type)
	{
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
                    player->objMove(KEY_PRESS_SURFACE_UP,b,map->Colliders,activeNPC,NUM_ACTIVE_NPC);
					player->changeFrame(KEY_PRESS_SURFACE_UP);
					t1 = SDL_GetTicks();
                    break;

                case SDLK_DOWN:
                    player->objMove(KEY_PRESS_SURFACE_DOWN,b,map->Colliders,activeNPC,NUM_ACTIVE_NPC);
                    player->changeFrame(KEY_PRESS_SURFACE_DOWN);
					t1 = SDL_GetTicks();
					break;

                case SDLK_LEFT:
                    player->objMove(KEY_PRESS_SURFACE_LEFT,b,map->Colliders,activeNPC,NUM_ACTIVE_NPC);
					player->changeFrame(KEY_PRESS_SURFACE_LEFT);
					t1 = SDL_GetTicks();
                    break;

                case SDLK_RIGHT:
                    player->objMove(KEY_PRESS_SURFACE_RIGHT,b,map->Colliders,activeNPC,NUM_ACTIVE_NPC);
					player->changeFrame(KEY_PRESS_SURFACE_RIGHT);
					t1 = SDL_GetTicks();
                    break;
				case SDLK_i:

					openInventory = true;

					break;
				case SDLK_m:

					if(loc1eat)
					{
					openMenu1 = true;
					loc1eat= false;
					}
					if(loc2eat)
					
					{
					openMenu2 = true;
					loc2eat= false;
					}

					break;
				case SDLK_t:
					printf("6");
					openTaskSchedule = true;

					break;
				case SDLK_o:

					openInventory = false;
					openTaskSchedule = false;
					openMenu1 = false;
					openMenu2 = false;
					break;
		// Play high sound effect
		// case SDLK_1:

		// 	Mix_PlayChannel(-1, gHigh, 0);
		// 	break;

		// // Play medium sound effect
		// case SDLK_2:
		// 	Mix_PlayChannel(-1, gMedium, 0);
		// 	break;
		// case SDLK_9:
		// 	// If there is no music playing
		// 	if (Mix_PlayingMusic() == 0)
		// 	{
		// 		// Play the music
		// 		Mix_PlayMusic(gMusic, -1);
		// 	}
		// 	// If music is being played
		// 	else
		// 	{
		// 		// If the music is paused
		// 		if (Mix_PausedMusic() == 1)
		// 		{
		// 			// Resume the music
		// 			Mix_ResumeMusic();
		// 		}
		// 		// If the music is playing
		// 		else
		// 		{
		// 			// Pause the music
		// 			Mix_PauseMusic();
		// 		}
		// 	}
		// 	break;

		// case SDLK_0:
		// 	// Stop the music
		// 	Mix_HaltMusic();
		// 	break;

		default:
			break;
		}

		break;
	}

	break;
	}
	musicOnButton.handleEvent(&e);
	musicOffButton.handleEvent(&e);
}

void Game::update()
{
	player->objUpdate();
	player2->objUpdate();
	display = (string) (map->getRegion(player->getx(),player->gety()));
	if (!loadTextMedia())
				{
					printf("Failed to load text media for taskbar!\n");
				}

	t4 = SDL_GetTicks();
	if (t4-t3 > 10000){
		t3 = t4;
		posIndex++;
		if (posIndex>19){
			posIndex =0;
		}
		professor->setx(posArray[posIndex]->fst);
		professor->sety(posArray[posIndex]->snd);
	}

	professor->NPCMove(map->Colliders,player->getx(),player->gety());
	professor->objUpdate();

	gCamera.x = (player->getx() - 400);
	gCamera.y = (player->gety() - 300);

	if (player->inMotion == false) {
		t2 = SDL_GetTicks();
		if (t2-t1 > 100){
			player->frame = 0;
		}
	} 

	player->inMotion = false;

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

void Game::render()
{
	SDL_RenderClear(gRenderer);
	map->DrawMap(gCamera.x, gCamera.y);		 // draw map
	player->objRender(gCamera.x, gCamera.y); // players over map
	// player->objRender();
	player2->objRender(gCamera.x, gCamera.y);
	professor->objRender();
	map->DrawplayerOneScore(); // scoreboard over map
	map->DrawHappinessBarU();
	map->DrawHappinessBarO();

	SDL_Rect fillRect = {0, 500, 800, 100}; // task bar over map
	SDL_SetRenderDrawColor(gRenderer, 192, 192, 192, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect);

	// Render black outlined quad
	SDL_Rect outlineRect = {0, 500, 800, 103};
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0000, 0x00, 0xFF);
	SDL_RenderDrawRect(gRenderer, &outlineRect);
	if (openInventory)
	{

		SDL_Rect fillRect1 = {0, 200, 800, 100}; // task bar over map
		SDL_SetRenderDrawColor(gRenderer, 192, 192, 192, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRect1);
		for (int i = 0; i < 2; i++)
		{

			string s = player->getIElem(player->inventoryItems, i);
			map->Drawitems(s, i);
		}
	}
		if (openTaskSchedule)
	{

		SDL_Rect fillRect2 = {200, 200, 300, 300}; // task bar over map
		SDL_SetRenderDrawColor(gRenderer, 192, 192, 192, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRect2);
		for (int i = 0; i < 2; i++)
		{

			string s = player->getIElem(player->inventoryItems, i);
			map->Drawitems(s, i);
		}
	}
		if (openMenu1)
	{

		SDL_Rect fillRect3 = {200, 200, 300, 300}; // task bar over map
		SDL_SetRenderDrawColor(gRenderer, 192, 192, 192, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRect3);
		for (int i = 0; i < 2; i++)
		{

						map->DrawMenu("menu1");
		}
	}
		if (openMenu2)
	{

		SDL_Rect fillRect4 = {200, 200, 300, 300}; // task bar over map
		SDL_SetRenderDrawColor(gRenderer, 192, 192, 192, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRect4);
		for (int i = 0; i < 2; i++)
		{


			map->DrawMenu("menu2");
		}
	}
	gTextTexture.render(300, 530); // text over task bar
	gHungerTexture.render(580, 90); // text over task bar
	gMoneyTexture.render(580, 115); // text over task bar
	gTaskCompletedTexture.render(580, 140); // text over task bar

	gTimeTextTexture.render( 300,50 );
	if (musicOn)
	{
		musicOnButton.renderMusic();
	}
	if (!musicOn)
	{
		printf("5");
		musicOffButton.renderMusic();
	}
	SDL_RenderPresent(gRenderer);
}

void Game::clean()
{
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	SDL_Quit();
	gbtexture1.free();
}

bool Game::running()
{
	if (isRunning)
	{
		return true;
	}
	else
	{
		return false;
	}
}
