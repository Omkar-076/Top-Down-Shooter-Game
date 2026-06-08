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
	ShootRequest shootRequest;
public:
	Player();
	void update(int movement, int mx, int my, bool wantsToShoot, float deltaTime);
	void render(SDL_Renderer *renderer);
};