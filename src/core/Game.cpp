#include "Game.h"
#include "input.h"
#include<SDL.h>
#include<SDL_ttf.h>
#include<iostream>
#include<string>
Game::Game() : WINDOW_WIDTH(800), WINDOW_HEIGHT(600){
	window = nullptr;
    renderer = nullptr;
	fontSmall = nullptr;
	fontMedium = nullptr;
	fontLarge = nullptr;
    running = true;
    request = { 0,0,0,0 };
    gameState = PLAYING;
    score = 0;
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
    gameState = PLAYING;
    Uint32 lastTime = SDL_GetTicks();
    srand((unsigned int)time(NULL));
    while (running){
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime)/1000.0f;
        lastTime = currentTime;

        Input::handleInput(running);
        update(deltaTime);
        render();

    }
}

void Game::restart() {
    player.restart();
    entityManager.restart();
    gameState = PLAYING;
    score = 0;
    Input::wantsToRestart = false;
}

void Game::update(float deltaTime){
    if (gameState == PLAYING) {
        player.update(Input::movement, Input::mx, Input::my, Input::wantsToShoot, deltaTime);
        if (player.hasShootRequest()) {
            request = player.consumeShootRequest();
            entityManager.createBullet(request);
        }
        score += entityManager.update(player.rect, deltaTime);
        if (entityManager.hasPlayerDied()) {
            gameState = GAME_OVER;
        }
    }
    else if (gameState == GAME_OVER) {
        if (Input::wantsToRestart) {
            restart();
            Input::wantsToRestart = false;
        }
    }
}
void Game::render(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    std::string scoreStr = "Score: " + std::to_string(score);

    if (gameState == PLAYING) {
        player.render(renderer);
        entityManager.renderBullets(renderer);
        entityManager.renderEnemies(renderer);
        SDL_Surface* scoreSurface = TTF_RenderText_Solid(fontSmall, scoreStr.c_str(), {255,255,255,255});
        if (!scoreSurface) {
            std::cout << "Surface creation Failed: " << TTF_GetError() << std::endl;
            return;
        }

        SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
        if (!scoreTexture) {
            std::cout << "Texture creation Failed: " << TTF_GetError() << std::endl;
            return;
        }
        SDL_Rect scoreTextRect = { 10, 10, 100, 30 };
        SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreTextRect);

        SDL_FreeSurface(scoreSurface);
        SDL_DestroyTexture(scoreTexture);
    }
    else if (gameState == GAME_OVER) {
        SDL_Surface* surface = TTF_RenderText_Solid(fontLarge, "Game Over", { 255,0,0,255 });
        if (!surface) {
            std::cout << "Surface creation Failed: " << TTF_GetError() << std::endl;
            return;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!texture) {
            std::cout << "Texture creation Failed: " << TTF_GetError() << std::endl;
            return;
        }
        SDL_Rect textRect = { 300, 200, 200, 75 };
        SDL_RenderCopy(renderer, texture, NULL, &textRect);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        surface = TTF_RenderText_Solid(fontSmall, scoreStr.c_str(), { 255,255,255,255 });
        if (!surface) {
            std::cout << "Surface creation Failed: " << TTF_GetError() << std::endl;
            return;
        }
        
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!texture) {
            std::cout << "Texture creation Failed: " << TTF_GetError() << std::endl;
            return;
        }
        textRect = { 350, 275, 100, 30 };
        SDL_RenderCopy(renderer, texture, NULL, &textRect);
        
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        SDL_Rect restartRect = { 340,325,120,50 };
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &restartRect);

        if ((Input::mx >= restartRect.x && Input::mx <= (restartRect.x + restartRect.w)) && (Input::my >= restartRect.y && Input::my <= (restartRect.y + restartRect.h))){
            surface = TTF_RenderText_Shaded(fontSmall, "Restart (R)", { 255,255,255,255 }, { 255,255,255,150 });
        }
        else {
            surface = TTF_RenderText_Shaded(fontSmall, "Restart (R)", { 255,255,255,255 }, { 255,175,0,150 });
        }
        if (!surface) {
            std::cout << "Surface creation Failed: " << TTF_GetError() << std::endl;
            return;
        }

        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!texture) {
            std::cout << "Texture creation Failed: " << TTF_GetError() << std::endl;
            return;
        }
        textRect = { 343, 330, 114, 40 };
        SDL_RenderCopy(renderer, texture, NULL, &textRect);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    SDL_RenderPresent(renderer);
}
