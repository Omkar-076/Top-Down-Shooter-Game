#pragma once
#include<SDL.h>
#include<SDL_ttf.h>
#include "..\entities\Player.h"
#include"..\systems\EntityManager.h"
#include "Input.h"
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
	int score;
	SDL_Rect restartRect;
	struct waveInfo {
		int enemyNumber;
		float spawnInterval;
	};
	std::vector<waveInfo> waves;
	int waveNumber;
public:
	Game();
	void init();
	void run();
	void restart();

	void startWave(waveInfo);
	
	void update(float);
	void render();
};