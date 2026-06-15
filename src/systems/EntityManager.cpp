#include"EntityManager.h"
#include"../entities/Bullet.h"
#include"Collision.h"
#include"../entities/Player.h"

EntityManager::EntityManager(){
	spawnInterval = 2;
	spawnTimer = 0;
	isPlayerDead = false;
	playerRect = { 0,0,0,0 };
}
void EntityManager::createBullet(ShootRequest shootRequest) {
	Bullet bullet(shootRequest);
	bulletVector.push_back(bullet);
}
void EntityManager::updateBullets(float deltaTime) {
	for (int i = 0; i < bulletVector.size(); i++)
	{
		bulletVector[i].update(deltaTime);
	}
	for (int i = 0; i < bulletVector.size(); i++)
	{
		if (bulletVector[i].isDead()) {
			bulletVector.erase(bulletVector.begin() + i);
			i -= 1;
		}
	}
}
void EntityManager::renderBullets(SDL_Renderer* renderer) {
	for (int i = 0; i < bulletVector.size(); i++)
	{
		bulletVector[i].render(renderer);
	}
}

//Enemy

void EntityManager::enemySpawner(float deltaTime) {
	spawnTimer += deltaTime;
	while (spawnTimer >= spawnInterval) {
		createEnemy();
		spawnTimer -= spawnInterval;
	}
}

void EntityManager::createEnemy() {
	float ex, ey;
	enum side { LEFT, UP, RIGHT, DOWN };
	side side;
	int decider = rand() % 4;
	switch (decider) {
	case 0:
		side = LEFT;
		ex = -50;
		ey = ((int)rand()) % 600;
		break;
	case 1:
		side = UP;
		ex = (int)(rand()) % 800;
		ey = -50;
		break;
	case 2:
		side = RIGHT;
		ex = 850;
		ey = (int)(rand()) % 600;
		break;
	case 3:
		side = DOWN;
		ex = (int)(rand()) % 800;
		ey = 650;
		break;
	default:
		side = UP;
		ex = -50;
		ey = (int)(rand()) % 600;
	}
	
	Enemy enemy(ex, ey);
	enemyVector.push_back(enemy);
}

void EntityManager::updateEnemies(float deltaTime, float px, float py) {
	for (int i = 0; i < enemyVector.size(); i++)
	{
		enemyVector[i].update(deltaTime, px, py);
	}
	for (int i = 0; i < enemyVector.size(); i++)
	{
		if (enemyVector[i].isDead()) {
			enemyVector.erase(enemyVector.begin() + i);
			i -= 1;
		}
	}
}
void EntityManager::renderEnemies(SDL_Renderer* renderer) {
	for (int i = 0; i < enemyVector.size(); i++)
	{
		enemyVector[i].render(renderer);
	}
}

//Player

void EntityManager::updatePlayer(SDL_Rect rect) {
	this->playerRect = rect;
}

//Collision

void EntityManager::checkCollision(){
	for (int i = 0; i < enemyVector.size(); i++) {
		for (int j = 0; j < bulletVector.size(); j++) {
			if (Collision::isColliding(enemyVector[i].rect, bulletVector[j].rect)) {
				bulletVector[j].markDead();
				enemyVector[i].markDead();
				break;
			}
		}
	}

	for (int i = 0; i < enemyVector.size(); i++){
		if (Collision::isColliding(playerRect, enemyVector[i].rect)) {
			isPlayerDead = true;
		}
	}

}