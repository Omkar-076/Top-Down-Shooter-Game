#pragma once
#include<SDL_ttf.h>
#include "..\entities\Player.h"
#include"..\systems\EntityManager.h"
#include"..\systems\TextureManager.h"
class Game {
	SDL_Window* window;
	SDL_Renderer* renderer;
	const int WINDOW_HEIGHT;
	const int WINDOW_WIDTH;
	TTF_Font* fontSmall;
	TTF_Font* fontMedium;
	TTF_Font* fontLarge;
	bool running;
	Player player;
	ShootRequest request;
	enum GameState { PLAYING, GAME_OVER };
	GameState gameState;
	EntityManager entityManager;
	TextureManager textureManager;
	int score;
	SDL_Rect restartRect;
	int waveNumber;
	int baseCount;
	float minInterval, maxInterval, intervalMultiplier, enemyMultiplier;
	SDL_Rect bgRect;
	SDL_Surface* bgSurface;
	SDL_Texture* bgTexture;
public:
	Game();
	void init();
	void run();
	void restart();

	void startWave(int);
	
	void update(float);
	void render();
};