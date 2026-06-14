#pragma once
#include<SDL.h>
class Enemy {
	float ex, ey, ew, eh;
	float dirX, dirY,length;
	float speed;
	bool isAlive;
	
public:
	SDL_Rect rect;
	Enemy();
	bool isDead();
	void markDead();
	void update(float deltaTime, float px, float py);
	void render(SDL_Renderer* renderer);
};