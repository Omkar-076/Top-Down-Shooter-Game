#include"Enemy.h"
#include<iostream>
#include<SDL.h>
Enemy::Enemy(float ex, float ey, float speed, Enemy::EnemyType type) {
	this->ex = ex;
	this->ey = ey;
	this->speed = speed;
	this->type = type;
	dirX = dirY = length = 0;
	isAlive = true;
	rect = { (int)ex, (int)ey, (int)ew, (int)eh };
	hitbox = { (int)ex, (int)ey, (int)ew, (int)eh };
	rotation = 0; 

	switch(type){
	case NORMAL:
		health = 1;
		scoreValue = 10;
		ew = 35;
		eh = 35;
		break;
	case TANK:
		health = 3;
		scoreValue = 15;
		ew = 50;
		eh = 50;
		this->speed -= 20;
		break;
	default:
		health = 1;
		scoreValue = 10;
		ew = 35;
		eh = 35;
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
		hitbox = rect;
		rotation = atan2(dirY, dirX) * 180 / M_PI - 60;
	}
}

void Enemy::render(SDL_Renderer* renderer, SDL_Texture* texture) {
	SDL_RenderCopyEx(renderer, texture, nullptr, &rect, rotation, nullptr, SDL_FLIP_NONE);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 100);
	SDL_RenderFillRect(renderer, &hitbox);
}
bool Enemy::isDead() {
	return (!isAlive);
}
void Enemy::markDead() {
	isAlive = false;
}
bool Enemy::takeDamage() {
	health--;
	if (health <= 0) {
		markDead();
		return true;
	}
	return false;
}
int Enemy::getScoreValue() {
	return scoreValue;
}