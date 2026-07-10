#include "Game.h"
#include "input.h"
#include<SDL.h>
#include<SDL_ttf.h>
#include<iostream>
#include<string>
#include<SDL_image.h>
#include<SDL_mixer.h>
Game::Game() : WINDOW_WIDTH(800), WINDOW_HEIGHT(600), MUSIC_VOLUME(32), SOUND_VOLUME(50){
	window = nullptr;
    renderer = nullptr;
	fontSmall = nullptr;
	fontMedium = nullptr;
	fontLarge = nullptr;
    running = true;
    request = { 0,0,0,0 };
    gameState = PLAYING;
    score = 0;
    restartRect = { 340,325,120,50 };
    waveNumber = 1;

    baseCount = 5;
    minInterval = 0.3;
    maxInterval = 1.8;
    intervalMultiplier= 0.35;
    enemyMultiplier=3;
    speedMultiplier = 0.20;
    maxEnemiesPerWave = 50;

    bgRect = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };
    bgSurface = nullptr;
    bgTexture = nullptr;

    
}
void Game::init() {
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		std::cout << "SDL INIT Failed" << std::endl;
		exit(-1);
	}

	window = SDL_CreateWindow(  
        "ZombieLand Survival",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int requestedFlags = IMG_INIT_PNG;
    int flags = IMG_Init(requestedFlags);
    if ((flags & requestedFlags) != requestedFlags) {
        std::cout << "IMG Init Failed: " << IMG_GetError() << std::endl;
    }

    if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048) < 0) {
        std::cout << "MIX INIT Failed: " << Mix_GetError() << std::endl;
    }

    if (TTF_Init() == -1) {
        std::cout << "TTF Init Failed: " << TTF_GetError() << std::endl;
    }
    fontLarge = TTF_OpenFont("assets/fonts/Arial.ttf", 100);
    fontMedium = TTF_OpenFont("assets/fonts/Arial.ttf", 50);
    fontSmall = TTF_OpenFont("assets/fonts/Arial.ttf", 24);
    if (!(fontSmall && fontMedium && fontLarge)) {
        std::cout << "Font Load Failed: " << TTF_GetError() << std::endl;
    }
    Input::init();

    //Load in all images
    
    bgSurface = IMG_Load("assets/images/background.png");
    if (!bgSurface) {
        std::cout << "Surface creation Failed: " << IMG_GetError() << std::endl;
        return;
    }
    bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    if (!bgTexture) {
        std::cout << "Texture creation Failed: " << SDL_GetError() << std::endl;
        return;
    }
    SDL_FreeSurface(bgSurface);

    textureManager.load(renderer, "player", "assets/images/Player.png");
    player.setTexture(textureManager.get("player"));

    textureManager.load(renderer, "enemy", "assets/images/Enemy.png");
    textureManager.load(renderer, "bullet","assets/images/Bullet.png");
    entityManager.setTextures(textureManager.get("enemy"),textureManager.get("bullet"));

    //Load in all Audio

    audioManager.loadSound("gunshot", "assets/audio/sounds/gunshot.mp3");
    audioManager.loadSound("gameOver", "assets/audio/sounds/gameOver.mp3");
    audioManager.loadSound("enemyDeath", "assets/audio/sounds/enemyDeath.mp3");
    audioManager.loadMusic("background", "assets/audio/music/background.mp3");
    audioManager.setMusicVolume(MUSIC_VOLUME);
    audioManager.setSoundVolume(SOUND_VOLUME);

}
void Game::run() {

    gameState = PLAYING;
    audioManager.playMusic("background");
    Uint32 lastTime = SDL_GetTicks();
    srand((unsigned int)time(NULL));
    while (running){
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime)/1000.0f;
        lastTime = currentTime;

        Input::handleInput(running);
        update(deltaTime);
        render();
        Input::endFrame();
    }
}

void Game::startWave(int waveNumber) {
    int enemyNumber;
    float spawnInterval;
    float enemySpeedMultiplier = 0;
    enemyNumber = baseCount + enemyMultiplier*(waveNumber-1);
    enemyNumber = std::min(maxEnemiesPerWave, enemyNumber);
    spawnInterval = std::max(minInterval, maxInterval-intervalMultiplier*(waveNumber/2));
    if (waveNumber >= 15) {
        enemySpeedMultiplier = speedMultiplier * ((waveNumber-15) *2 / 5.0 );
    }
    entityManager.configWave(enemyNumber, spawnInterval, enemySpeedMultiplier, waveNumber);
    
}

void Game::restart() {
    player.restart();
    entityManager.restart();
    request = { 0,0,0,0 };
    gameState = PLAYING;
    score = 0;
    waveNumber = 14;
    bgRect = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };
}

void Game::update(float deltaTime){
    if (gameState == PLAYING) {

        player.update(Input::movement, Input::mx, Input::my, Input::wantsToShoot, deltaTime);
        if (player.hasShootRequest()) {
            request = player.consumeShootRequest();
            audioManager.playSound("gunshot");
            entityManager.createBullet(request);
        }
        score += entityManager.update(player.rect, deltaTime);
        if (entityManager.hasPlayerDied()) {
            gameState = GAME_OVER;
            audioManager.playSound("gameOver");
        }
        if ((entityManager.shouldWaveEnd())){
            startWave(waveNumber);
            waveNumber++;
        }
        int temp = entityManager.enemiesDiedThisFrame();
        while (temp > 0) {
            audioManager.playSound("enemyDeath");
            temp--;
        }
    }
    else if (gameState == GAME_OVER) {
        if (Input::keyPressed(SDL_SCANCODE_R)) {
            restart();
        }
        if ((Input::wantsToShoot)&&(Input::mx >= restartRect.x && Input::mx <= (restartRect.x + restartRect.w)) && (Input::my >= restartRect.y && Input::my <= (restartRect.y + restartRect.h))) {
            restart();
        }
    }
}
void Game::render(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    std::string scoreStr = "Score: " + std::to_string(score);
    std::string waveStr = "Wave: " + std::to_string(waveNumber-1);
    if (gameState == PLAYING) {
        
        SDL_RenderCopy(renderer, bgTexture, nullptr, &bgRect);

        entityManager.renderBullets(renderer);
        entityManager.renderEnemies(renderer);
        player.render(renderer);

        SDL_Rect Scoreboard = { 0,0,115,70 };
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 75);
        SDL_RenderFillRect(renderer, &Scoreboard);

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
        SDL_Rect scoreTextRect = { 10, 5, 100, 30 };
        SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreTextRect);

        SDL_FreeSurface(scoreSurface);
        SDL_DestroyTexture(scoreTexture);

        SDL_Surface* waveSurface = TTF_RenderText_Solid(fontSmall, waveStr.c_str(), { 255,255,255,255 });
        if (!waveSurface) {
            std::cout << "Surface creation Failed: " << TTF_GetError() << std::endl;
            return;
        }

        SDL_Texture* waveTexture = SDL_CreateTextureFromSurface(renderer, waveSurface);
        if (!waveTexture) {
            std::cout << "Texture creation Failed: " << TTF_GetError() << std::endl;
            return;
        }
        SDL_Rect waveTextRect = { 10, 40, 100, 30 };
        SDL_RenderCopy(renderer, waveTexture, NULL, &waveTextRect);

        SDL_FreeSurface(waveSurface);
        SDL_DestroyTexture(waveTexture);

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
Game::~Game() {
    SDL_DestroyTexture(bgTexture);
    TTF_CloseFont(fontSmall);
    TTF_CloseFont(fontMedium);
    TTF_CloseFont(fontLarge);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}