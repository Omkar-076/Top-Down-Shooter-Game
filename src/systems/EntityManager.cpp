#include"EntityManager.h"
#include"../entities/Bullet.h"
#include"Collision.h"

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

void EntityManager::createEnemy() {
	Enemy enemy;
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
			std::cout << "Enemy Killed" << std::endl;
		}
	}
}
void EntityManager::renderEnemies(SDL_Renderer* renderer) {
	for (int i = 0; i < enemyVector.size(); i++)
	{
		enemyVector[i].render(renderer);
	}
}

//Collision

void EntityManager::checkCollision(){
	for (int i = 0; i < enemyVector.size(); i++) {
		for (int j = 0; j < bulletVector.size(); j++) {
			if (Collision::isColliding(enemyVector[i].rect, bulletVector[j].rect)) {
				std::cout << "Collision of enemy"<<i<<" and bullet"<<j<< std::endl;
				bulletVector[j].markDead();
				enemyVector[i].markDead();
				break;
			}
		}
	}

}