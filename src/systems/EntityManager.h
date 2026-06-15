#pragma once
#include<iostream>
#include<vector>
#include"../entities/ShootRequest.h"
#include"../entities/Bullet.h"
#include"../entities/Enemy.h"
#include<SDL.h>
class EntityManager {
	std::vector<Bullet> bulletVector;
	std::vector<Enemy> enemyVector;
	float spawnInterval, spawnTimer;
	SDL_Rect playerRect;
	
public:
	bool isPlayerDead;

	EntityManager();
	void createBullet(ShootRequest shootRequest);
	void updateBullets(float deltaTime);
	void renderBullets(SDL_Renderer *renderer);

	void enemySpawner(float deltaTime);
	void createEnemy();
	void updateEnemies(float deltaTime, float px, float py);
	void renderEnemies(SDL_Renderer* renderer);

	void updatePlayer(SDL_Rect);

	void checkCollision();
};