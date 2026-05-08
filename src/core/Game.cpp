#include "Game.h"
#include<SDL.h>
#include<SDL_ttf.h>
#include<iostream>
Game::Game() : WINDOW_WIDTH(800), WINDOW_HEIGHT(600){
	window = nullptr;
	renderer = nullptr;
	fontSmall = nullptr;
	fontMedium = nullptr;
	fontLarge = nullptr;
}

void Game::init() {
	std::cout << "Hello" << std::endl;
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		std::cout << "SDL INIT Failed" << std::endl;
		exit(-1);
	}

	window = SDL_CreateWindow(  
        "My First SDL Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (TTF_Init() == -1) {
        std::cout << "TTF Init Failed: " << TTF_GetError() << std::endl;
    }
    fontLarge = TTF_OpenFont("assets/fonts/Arial.ttf", 100);
    fontMedium = TTF_OpenFont("assets/fonts/Arial.ttf", 50);
    fontSmall = TTF_OpenFont("assets/fonts/Arial.ttf", 24);
    if (!(fontSmall && fontMedium && fontLarge)) {
        std::cout << "Font Load Failed: " << TTF_GetError() << std::endl;
    }
}
void Game::run() {
	std::cout << "World" << std::endl;
}
