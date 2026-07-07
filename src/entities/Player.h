#pragma once
#include<SDL.h>
#include"ShootRequest.h"
class Player {
	float px, py, dX, dY;
	float cPx, cPy;
	int pw, ph;
	float MdirX, MdirY;
	float speed;
	float length;
	bool wantsToShoot;
	float offset;
	bool isAlive;
	ShootRequest shootRequest;
	SDL_Texture* texture;
public:
	SDL_Rect rect;
	void setTexture(SDL_Texture* texture);
	Player();
	float getPx();
	float getPy();
	void update(int movement, int mx, int my, bool wantsToShoot, float deltaTime);
	void render(SDL_Renderer *renderer);
	bool hasShootRequest();
	void markDead();
	bool isDead();
	ShootRequest consumeShootRequest();
	void restart();
};