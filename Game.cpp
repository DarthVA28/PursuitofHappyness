#include "Game.hpp"
#include "TM.hpp"
#include "Object.hpp"
#include "Map.hpp"
#include "Tuple.hpp"
// #include <SDL2/SDL_mixer.h>


// Mix_Music *gMusic = nullptr;

// //The sound effects that will be used
// Mix_Chunk *gScratch = NULL;
// Mix_Chunk *gHigh = NULL;
// Mix_Chunk *gMedium = NULL;
// Mix_Chunk *gLow = NULL;


//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//Button constants
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 1;


bool firstScreen = true;
bool Game :: firstCheck =true;
SDL_Renderer* Game::gRenderer = nullptr;

enum LButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_TOTAL = 4
};

//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );
		
		#if defined(SDL_TTF_MAJOR_VERSION)
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif
		
		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};

//The mouse button
class LButton
{
	public:
		//Initializes internal variables
		LButton();

		//Sets top left position
		void setPosition( int x, int y );

		//Handles mouse event
		void handleEvent( SDL_Event* e );
	
		//Shows button sprite
		void render();

	private:
		//Top left position
		SDL_Point mPosition;

		//Currently used global sprite
		LButtonSprite mCurrentSprite;
};

//Mouse button sprites
SDL_Rect gSpriteClips[ BUTTON_SPRITE_TOTAL ];
LTexture gButtonSpriteSheetTexture;

//Buttons objects
LButton gButtons[ TOTAL_BUTTONS ]; 

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}
LTexture gbtexture1 ;
bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;
	

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( Game::gRenderer, loadedSurface );
        
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( Game::gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	
	//Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( Game::gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
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

	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void LButton::setPosition( int x, int y )
{
	mPosition.x = x;
	mPosition.y = y;
}

void LButton::handleEvent( SDL_Event* e )
{
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < mPosition.x )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > mPosition.x + BUTTON_WIDTH )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < mPosition.y )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > mPosition.y + BUTTON_HEIGHT )
		{
			inside = false;
		}

		//Mouse is outside button
		if( !inside )
		{
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch( e->type )
			{
				case SDL_MOUSEMOTION:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;
			
				case SDL_MOUSEBUTTONDOWN:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
				firstScreen = false;
				Game :: firstCheck = false;
				break;
				
				case SDL_MOUSEBUTTONUP:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
				break;
			}
		}
	}
}
	
void LButton::render()
{
	//Show current button sprite
	gButtonSpriteSheetTexture.render( mPosition.x, mPosition.y, &gSpriteClips[ mCurrentSprite ] );
	
	
}


//------------------------------------------------------------------------------- MUSIC---------------------------------------------------------------------------------------------
LTexture gPromptTexture;

// bool loadMusicMedia()
// {
// 	//Loading success flag
// 	bool success = true;

// 	//Load prompt texture


// 	//Load music
// 	gMusic = Mix_LoadMUS( "/home/mastercoder/Desktop/copTask2/IITGame-master/assets/beat.wav" );
// 	if( gMusic == NULL )
// 	{
// 		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
// 		success = false;
// 	}
	
// 	//Load sound effects
// 	gScratch = Mix_LoadWAV( "/home/mastercoder/Desktop/copTask2/IITGame-master/assets/scratch.wav" );
// 	if( gScratch == NULL )
// 	{
// 		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
// 		success = false;
// 	}
	
// 	gHigh = Mix_LoadWAV( "/home/mastercoder/Desktop/copTask2/IITGame-master/assets/high.wav" );
// 	if( gHigh == NULL )
// 	{
// 		printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
// 		success = false;
// 	}

// 	gMedium = Mix_LoadWAV( "/home/mastercoder/Desktop/copTask2/IITGame-master/assets/medium.wav" );
// 	if( gMedium == NULL )
// 	{
// 		printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
// 		success = false;
// 	}

// 	gLow = Mix_LoadWAV( "/home/mastercoder/Desktop/copTask2/IITGame-master/assets/low.wav" );
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

//-----------------------------------START SCREEN---------------------------------------------
bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load sprites
	if( !gbtexture1.loadFromFile( "./assets/button.png" ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}
	else if( !gButtonSpriteSheetTexture.loadFromFile( "./assets/button.png" ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}
	else
	{
		//Set sprites
		for( int i = 0; i < BUTTON_SPRITE_TOTAL; ++i )
		{
			gSpriteClips[ i ].x = 0;
			gSpriteClips[ i ].y = i * 200;
			gSpriteClips[ i ].w = BUTTON_WIDTH;
			gSpriteClips[ i ].h = BUTTON_HEIGHT;
		}

		//Set buttons in corners
		gButtons[ 0 ].setPosition( 300, 350 );
		
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

Object* player;
Object* player2;
Map* map;

SDL_Rect Game::gCamera = {0,0,800,600};


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

    player = new Object("assets/p1.png", 400,300);
    player = new Object("assets/p1.png", 9412,4532);
    player2 = new Object("assets/p2.png", 128,128);
    map = new Map(); 
}

// void Game::init(const char* win_title, int xpos, int ypos, int h, int w, bool fs) {
//     //Initialization flag
// 	bool success = true;
//     int flags = 0;
//     cnt = w-128;
//     if (fs) {
//         flags = SDL_WINDOW_FULLSCREEN;
//     }

// 	//Initialize SDL
// 	if( SDL_Init(SDL_INIT_VIDEO| SDL_INIT_AUDIO ) < 0 )
// 	{
// 		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
// 		success = false;
// 	}
	
// 	else
// 	{	//Set texture filtering to linear
// 		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
// 		{
// 			printf( "Warning: Linear texture filtering not enabled!" );
// 		}
// 		//Create window
// 		gWindow = SDL_CreateWindow(win_title, xpos, ypos, h, w, flags);
// 		if( gWindow == NULL )
// 		{
// 			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
// 			success = false;
// 		}
// 		else
// 		{
// 			//Get window surface
//             // gScreenSurface = SDL_GetWindowSurface( gWindow );
// 			gRenderer = SDL_CreateRenderer(gWindow,-1,0);
			
// 			// gRenderer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			
// 			if  (gRenderer == NULL) {
// 					printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );
// 					success = false;
// 			} 
// 			 //Initialize SDL_mixer
// 			// if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
// 			// {
// 			// 	printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
// 			// 	success = false;
// 			// }
			
// 			else {
// 				if( !loadMedia() ) {
// 					printf( "Failed to load media!\n" );
// 				}
// 				// if( !loadMusicMedia() ) {
// 				// 		printf( "Failed to load music media!\n" );
// 				// }
//                 SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

//                 int imgFlags = IMG_INIT_PNG;
// 				if( !( IMG_Init( imgFlags ) & imgFlags ) )
// 				{
// 					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
// 					success = false;
// 				}
// 				// if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
// 				// {
// 				//     printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
// 				//     success = false;
// 				// }
// 			}
// 		}
// 	}

//     if (success) {
//         isRunning = true;
//     } else {
//         isRunning = false;
//     }

//     player = new Object("assets/p1.png", 12376,2048);
//     player2 = new Object("assets/p2.png", 128,128);
//     map = new Map(); 
// }

void Game::handleEvent()  {
    SDL_Event e; 
    SDL_PollEvent(&e);
    
    bool quit = false;
    while(!quit && firstScreen)
    {
	while( SDL_PollEvent( &e ) != 0 )
	{
		//User requests quit
		if( e.type == SDL_QUIT )
		{
			quit = true;
		}
		// else if( e.type == SDL_KEYDOWN )
		// 			{
		// 				switch( e.key.keysym.sym )
		// 				{//Play high sound effect
		// 					case SDLK_1:
		// 					Mix_PlayChannel( -1, gHigh, 0 );
		// 					break;
							
		// 					//Play medium sound effect
		// 					case SDLK_2:
		// 					Mix_PlayChannel( -1, gMedium, 0 );
		// 					break;
		// 				case SDLK_9:
		// 					//If there is no music playing
		// 					if( Mix_PlayingMusic() == 0 )
		// 					{
		// 						//Play the music
		// 						Mix_PlayMusic( gMusic, -1 );
		// 					}
		// 					//If music is being played
		// 					else
		// 					{
		// 						//If the music is paused
		// 						if( Mix_PausedMusic() == 1 )
		// 						{
		// 							//Resume the music
		// 							Mix_ResumeMusic();
		// 						}
		// 						//If the music is playing
		// 						else
		// 						{
		// 							//Pause the music
		// 							Mix_PauseMusic();
		// 						}
		// 					}
		// 					break;
							
		// 					case SDLK_0:
		// 					//Stop the music
		// 					Mix_HaltMusic();
		// 					break;
		// 				}
		// 			}
		
		//Handle button events
		for( int i = 0; i < TOTAL_BUTTONS; ++i )
		{
			gButtons[ i ].handleEvent( &e );
		}
	}

	//Clear screen
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );


	SDL_RenderClear( gRenderer );
	SDL_Rect cm = {0,0,50,50};
        gbtexture1.render(40,40,&cm);
        gPromptTexture.render( 0, 0 );
	//Render buttons
	for( int i = 0; i < TOTAL_BUTTONS; ++i )
	{
		gButtons[ i ].render();
	}

	//Update screen
	SDL_RenderPresent( gRenderer );
    }
    
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
				// //Play high sound effect
				// case SDLK_1:
				// 	Mix_PlayChannel( -1, gHigh, 0 );
				// 	break;
				
				// //Play medium sound effect
				// case SDLK_2:
				// 	Mix_PlayChannel( -1, gMedium, 0 );
				// 	break;
				// case SDLK_9:
				// //If there is no music playing
				// 	if( Mix_PlayingMusic() == 0 )
				// 	{
				// 		//Play the music
				// 		Mix_PlayMusic( gMusic, -1 );
				// 	}
				// //If music is being played
				// 	else
				// 	{
				// 		//If the music is paused
				// 		if( Mix_PausedMusic() == 1 )
				// 		{
				// 			//Resume the music
				// 			Mix_ResumeMusic();
				// 		}
				// 		//If the music is playing
				// 		else
				// 		{
				// 			//Pause the music
				// 			Mix_PauseMusic();
				// 		}
				// 	}
				// 	break;
				
				// case SDLK_0:
				// 	//Stop the music
				// 	Mix_HaltMusic();
				// break;
                        
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
    gbtexture1.free();
    }

bool Game::running() {
    if (isRunning) {
        return true;
    } else {
        return false;
    }
}
