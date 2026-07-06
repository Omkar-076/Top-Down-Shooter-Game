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
	int enemiesToSpawn;
	bool isPlayerDead;
public:

	EntityManager();

	int update(SDL_Rect playerRect, float deltaTime);

	void createBullet(ShootRequest shootRequest);
	void updateBullets(float deltaTime);
	void renderBullets(SDL_Renderer *renderer);

	void enemySpawner(float deltaTime);
	void createEnemy();
	void updateEnemies(float deltaTime, float px, float py);
	void renderEnemies(SDL_Renderer* renderer);

	void updateEnemySpawner(int enemyNumber, float spawnInterval);

	bool hasPlayerDied();
	bool shouldWaveEnd();
	int checkCollision(SDL_Rect playerRect);

	void restart();
};