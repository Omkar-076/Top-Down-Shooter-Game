#pragma once
#include<SDL.h>
#include<SDL_ttf.h>
class Game {
	SDL_Window* window;
	SDL_Renderer* renderer;
	const int WINDOW_HEIGHT;
	const int WINDOW_WIDTH;
	TTF_Font* fontSmall;
	TTF_Font* fontMedium;
	TTF_Font* fontLarge;
public:
	Game();
	void init();
	void run();
};