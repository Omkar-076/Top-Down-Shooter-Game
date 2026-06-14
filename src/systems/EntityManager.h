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
public:
	void createBullet(ShootRequest shootRequest);
	void updateBullets(float deltaTime);
	void renderBullets(SDL_Renderer *renderer);

	void createEnemy();
	void updateEnemies(float deltaTime, float px, float py);
	void renderEnemies(SDL_Renderer* renderer);

	void checkCollision();
};