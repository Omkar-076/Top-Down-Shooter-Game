#include<iostream>
#include"Bullet.h"
#include"ShootRequest.h"
Bullet::Bullet(ShootRequest request){
	bx = request.spawnX;
	by = request.spawnY;
	dirX = request.dirX;
	dirY = request.dirY;
	bw = 24.0;
	bh = 6.0;
	speed = 500.0;
	isAlive = true;
	rect = { (int)bx, (int)by, (int)bw, (int)bh };
}

void Bullet::update(float deltaTime) {
	bx += speed * deltaTime * dirX;
	by += speed * deltaTime * dirY;

	rect = { (int)bx, (int)by, (int)bw, (int)bh };

	if ((bx < (0 - bw))  || (bx > 800/*WINDOW_WIDTH*/) || (by < (0-bh)) || (by > 600/*WINDOW_HEIGHT*/)) {
		isAlive = false;
	}

}

void Bullet::render(SDL_Renderer* renderer, SDL_Texture* texture) {
	SDL_RenderCopy(renderer, texture, nullptr, &rect);
}
bool Bullet::isDead() {
	return !(isAlive);
}
void Bullet::markDead() {
	isAlive = false;
}