#include<iostream>
#include"../systems/EntityManager.h"
#include"Bullet.h"
#include"ShootRequest.h"
Bullet::Bullet(ShootRequest request){
	std::cout << request.dirX << std::endl;
	px = request.spawnX;
	py = request.spawnY;
	dirX = request.dirX;
	dirY = request.dirY;
	pw = 10.0;
	ph = 10.0;
	speed = 100.0;

	
}
void Bullet::update(float deltaTime) {
	px += speed * deltaTime * dirX;
	py += speed * deltaTime * dirY;
}
void Bullet::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 119, 119, 119, 255);
	SDL_Rect rect = { (int)px, (int)py, pw, ph };
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderPresent(renderer);
}