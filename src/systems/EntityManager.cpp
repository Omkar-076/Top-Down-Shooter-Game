#include"EntityManager.h"
#include"../entities/Bullet.h"
#include"Collision.h"

EntityManager::EntityManager(){
	spawnInterval = 1.5;
	spawnTimer = 0;
	isPlayerDead = false;
	enemiesToSpawn = 0;
	maxOpeningBurst = 10.0;
	enemyTexture = bulletTexture = nullptr;
	enemiesDeadThisFrame = 0;
	enemySpeed = 60;
	baseEnemySpeed = 60;
	maxSpeed = 85;

}
void EntityManager::configWave(int enemyNumber, float spawnInterval, float speedMultiplier, int waveNumber) {
	enemiesToSpawn = enemyNumber;
	this->spawnInterval = spawnInterval;
	enemySpeed = baseEnemySpeed + baseEnemySpeed*speedMultiplier;
	enemySpeed = std::min(maxSpeed, enemySpeed);
	spawnTimer += (waveNumber / 4) * 3 * spawnInterval;
	spawnTimer = std::min(maxOpeningBurst*spawnInterval, spawnTimer);
}

bool EntityManager::shouldWaveEnd() {
	
	return (enemiesToSpawn == 0 && enemyVector.size() == 0);
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
		bulletVector[i].render(renderer, bulletTexture);
	}
}

//Enemy

void EntityManager::enemySpawner(float deltaTime) {
	spawnTimer += deltaTime;
	while (spawnTimer >= spawnInterval && enemiesToSpawn > 0) {
		createEnemy();
		spawnTimer -= spawnInterval;
		enemiesToSpawn--;
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
	
	Enemy enemy(ex, ey, enemySpeed);
	enemyVector.push_back(enemy);
}

void EntityManager::updateEnemies(float deltaTime, float px, float py) {
	enemiesDeadThisFrame = 0;
	for (int i = 0; i < enemyVector.size(); i++)
	{
		enemyVector[i].update(deltaTime, px, py);
	}
	for (int i = 0; i < enemyVector.size(); i++)
	{
		if (enemyVector[i].isDead()) {
			enemyVector.erase(enemyVector.begin() + i);
			i -= 1;
			enemiesDeadThisFrame += 1;
		}	
	}
}

void EntityManager::setTextures(SDL_Texture* enemyTexture, SDL_Texture* bulletTexture) {
		this->enemyTexture = enemyTexture;
		this->bulletTexture = bulletTexture;
}

void EntityManager::renderEnemies(SDL_Renderer* renderer) {
	for (int i = 0; i < enemyVector.size(); i++)
	{
		enemyVector[i].render(renderer,enemyTexture);
	}
}
int EntityManager::enemiesDiedThisFrame() {
	return enemiesDeadThisFrame;
}
bool EntityManager::hasPlayerDied() {
	return isPlayerDead;
}

//Collision

int EntityManager::checkCollision(SDL_Rect playerRect){
	int scoreEarnedThisFrame = 0;
	for (int i = 0; i < enemyVector.size(); i++) {
		for (int j = 0; j < bulletVector.size(); j++) {
			if (bulletVector[j].isDead()) {
				continue;
			}
			if (Collision::isColliding(enemyVector[i].rect, bulletVector[j].rect)) {
				bulletVector[j].markDead();
				enemyVector[i].markDead();
				scoreEarnedThisFrame += enemyVector[i].getScoreValue();
				break;
			}
		}
	}

	for (int i = 0; i < enemyVector.size(); i++){
		if (enemyVector[i].isDead()) {
			continue;
		}
		if (Collision::isColliding(playerRect, enemyVector[i].rect)) {
			isPlayerDead = true;
		}
	}
	return scoreEarnedThisFrame;
}

int EntityManager::update(SDL_Rect playerRect, float deltaTime) {
	
	enemySpawner(deltaTime);
	updateBullets(deltaTime);
	updateEnemies(deltaTime, (playerRect.x + playerRect.w/2),( playerRect.y + playerRect.h/2));
	return checkCollision(playerRect);
}

void EntityManager::restart() {
	bulletVector.clear();
	enemyVector.clear();
	isPlayerDead = false;
	spawnTimer = 0;
	enemiesToSpawn = 0;
	spawnInterval = 1.5;
	enemySpeed = 60;
}