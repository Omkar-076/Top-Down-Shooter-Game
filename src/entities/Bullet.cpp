#include<iostream>
#include"Bullet.h"
#include"ShootRequest.h"
Bullet::Bullet(ShootRequest request){
	bx = request.spawnX;
	by = request.spawnY;
	dirX = request.dirX;
	dirY = request.dirY;
	bw = 15.0;
	bh = 4.0;
	speed = 550.0;
	isAlive = true;
	rect = { (int)bx, (int)by, (int)bw, (int)bh };
	rotation = atan2(dirY, dirX)*180/M_PI;
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
	SDL_RenderCopyEx(renderer, texture, nullptr, &rect, rotation, nullptr, SDL_FLIP_NONE);
}
bool Bullet::isDead() {
	return !(isAlive);
}
void Bullet::markDead() {
	isAlive = false;
}