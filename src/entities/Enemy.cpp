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
	speed = 50;
	rect = { (int)ex, (int)ey, (int)ew, (int)eh };
}
void Enemy::update(float deltaTime, float px, float py) {
	dirX = px - ex;
	dirY = py - ey;
	length = sqrt(dirX * dirX + dirY * dirY);
	dirX /= length;
	dirY /= length;
	ex += dirX * speed * deltaTime;
	ey += dirY * speed * deltaTime;
	rect = { (int)ex, (int)ey, (int)ew, (int)eh };
}
void Enemy::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
}
bool Enemy::isDead() {
	return (!isAlive);
}
void Enemy::markDead() {
	isAlive = false;
}