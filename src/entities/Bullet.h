#pragma once
#include<SDL.h>
#include"ShootRequest.h"
class Bullet {
	float bx, by, bw, bh;
	float dirX, dirY;
	float speed;
	bool isAlive;
	
public:
	SDL_Rect rect;
	bool isDead();
	void markDead();
	Bullet(ShootRequest request);
	void update(float deltaTime);
	void render(SDL_Renderer* renderer);
};