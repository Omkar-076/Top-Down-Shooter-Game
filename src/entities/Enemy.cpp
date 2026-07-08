#include"Enemy.h"
#include<iostream>
#include<SDL.h>
Enemy::Enemy(float ex, float ey) {
	this->ex = ex;
	this->ey = ey;
	ew = 35;
	eh = 35;
	dirX = dirY = length = 0;
	isAlive = true;
	speed = 60;
	rect = { (int)ex, (int)ey, (int)ew, (int)eh };
	rotation = 0;
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
		rotation = atan2(dirY, dirX) * 180 / M_PI - 60;
	}
}

void Enemy::render(SDL_Renderer* renderer, SDL_Texture* texture) {
	SDL_RenderCopyEx(renderer, texture, nullptr, &rect, rotation, nullptr, SDL_FLIP_NONE);
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