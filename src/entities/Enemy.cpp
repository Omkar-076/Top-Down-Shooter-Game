#include"Enemy.h"
#include<iostream>
#include<SDL.h>
Enemy::Enemy(float ex, float ey) {
	this->ex = ex;
	this->ey = ey;
	ew = 25;
	eh = 25;
	dirX = dirY = length = 0;
	isAlive = true;
	speed = 60;
	rect = { (int)ex, (int)ey, (int)ew, (int)eh };
	texture = nullptr;
	EnemyType = NORMAL; //Later can make a system to decide between types.
	switch(EnemyType){
	case NORMAL:
		scoreValue = 10;
		break;
	default:
		scoreValue = 10;
		break;
	}
	
}
void Enemy::update(float deltaTime, float px, float py) {
	if (isAlive) {
		dirX = px - ex;
		dirY = py - ey;
		length = sqrt(dirX * dirX + dirY * dirY);
		if (length >= 0.0001) {
			dirX /= length;
			dirY /= length;
		}
		else {
			dirX = dirY = 0;
		}
		ex += dirX * speed * deltaTime;
		ey += dirY * speed * deltaTime;
		rect = { (int)ex, (int)ey, (int)ew, (int)eh };
	}
}
void Enemy::setTexture(SDL_Texture* enemyTexture) {
	texture = enemyTexture;
	std::cout << enemyTexture << std::endl;
}
void Enemy::render(SDL_Renderer* renderer, SDL_Texture* texture) {
	SDL_RenderCopy(renderer, texture, nullptr, &rect);
}
bool Enemy::isDead() {
	return (!isAlive);
}
void Enemy::markDead() {
	isAlive = false;
}
int Enemy::getScoreValue() {
	return scoreValue;
}