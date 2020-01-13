// using SDL, SDL_image, iostream and string
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <cmath>

// using declaration
using namespace std;

// screen constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// initialize SDL and create screen
bool init();

// loads media
bool loadMedia();

// frees media and shuts down SDL
void close();

// loads individual image as texture
SDL_Texture* loadTexture(string path);

// ---------------------------------------------------------------

// the window we'll be rendering to
SDL_Window* window = NULL;

// the window renderer
SDL_Renderer* renderer = NULL;

// --------------------------------------------------

bool init() {
	// initialize SDL
	SDL_Init(SDL_INIT_VIDEO);
	
	// set texture filtering to linear
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	
	// create window
	window = SDL_CreateWindow("Bouncing Cube Using SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	
	// create renderer for window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	// initialize renderer color
	
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	
	// initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	IMG_Init(imgFlags);
	
	return true;
}

bool loadMedia() {
	// nothing to load
	return true;
}

void close() {
	// destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;
	
	// quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture(string path) {
	// the final texture
	SDL_Texture* newTexture = NULL;
	
	// load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	
	// create texture from surface pixels
	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	
	// get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);
	
	return newTexture;
}

// ----------------------------------------------------------------------

int main(int argc, char* args[]) {
	// start up SDL and create window
	init();
	
	// load media
	loadMedia();
	
	// main loop flag
	bool running = true;
	
	// event handler
	SDL_Event e;
	
	int squareX = SCREEN_WIDTH/2;
	int squareY = SCREEN_HEIGHT/2;
	
	int squareXChange = 5;
	int squareYChange = 5;
	
	int r = 0x00;
	int g = 0x00;
	int b = 0x00;
	
	// while app is running
	while (running) {
		
		// handle events on queue
		while (SDL_PollEvent(&e) != 0) {
			
			// user requests quit
			if (e.type == SDL_QUIT) {
				running = false;
			}
		}
		
		// clear screen
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);
		
		// render black square
		SDL_Rect fillRect = { squareX, squareY, 50, 50 };
		SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
		SDL_RenderFillRect(renderer, &fillRect);
		
		if (squareX == SCREEN_WIDTH - 50) {
			squareXChange = -5;
			r = r + 5;
		}
		if (squareX == 0) {
			squareXChange = 5;
			g = g + 5;
		}
		if (squareY == SCREEN_HEIGHT - 50) {
			squareYChange = -5;
			b = g + 5;
		}
		if (squareY == 0) {
			squareYChange = 5;
			r = g + 5;
		}		
		
		squareX = squareX + squareXChange;
		squareY = squareY + squareYChange;
		
		// update screen
		SDL_RenderPresent(renderer);
		
		//Wait .01 seconds
		SDL_Delay(10);
	}
	
	// free resources and close SDL
	close();
	
	return 0;
}