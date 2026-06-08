#include "Game.h"
#include "input.h"
#include<SDL.h>
#include<SDL_ttf.h>
#include<iostream>
Game::Game() : WINDOW_WIDTH(800), WINDOW_HEIGHT(600){
	window = nullptr;
    renderer = nullptr;
	fontSmall = nullptr;
	fontMedium = nullptr;
	fontLarge = nullptr;
    running = true;
}
void Game::init() {
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
    Uint32 lastTime = SDL_GetTicks();
    while (running){
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime)/1000.0f;
        lastTime = currentTime;

        Input::handleInput(running);
        update(deltaTime);
        render();

    }
}
void Game::update(float deltaTime){
    player.update(Input::movement, Input::mx, Input::my, Input::wantsToShoot, deltaTime);
}
void Game::render(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    player.render(renderer);
    SDL_RenderPresent(renderer);
}
