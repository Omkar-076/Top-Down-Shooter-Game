#pragma once
#include"../systems/EntityManager.h"
#include<SDL.h>
#include"ShootRequest.h"
class Bullet {
	float px, py, pw, ph;
	float dirX, dirY;
	float speed;

public:
	Bullet(ShootRequest request);
	void update(float deltaTime);
	void render(SDL_Renderer* renderer);
};