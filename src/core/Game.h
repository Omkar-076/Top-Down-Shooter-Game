#pragma once
#include<SDL_ttf.h>
#include<array>
#include "..\entities\Player.h"
#include"..\systems\EntityManager.h"
#include"..\systems\TextureManager.h"
#include"..\systems\AudioManager.h"
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
	AudioManager audioManager;
	int score;
	SDL_Rect restartRect;
	int waveNumber;
	int baseCount,maxEnemiesPerWave;
	float minInterval, maxInterval, intervalMultiplier, enemyMultiplier,speedMultiplier;
	std::array<SDL_Texture*,8> playerTextures;
	SDL_Rect bgRect;
	SDL_Surface* bgSurface;
	SDL_Texture* bgTexture;
	const int MUSIC_VOLUME;
	const int SOUND_VOLUME;
public:
	Game();
	void init();
	void run();
	void restart();

	void startWave(int);
	
	void update(float);
	void render();

	~Game();
};
