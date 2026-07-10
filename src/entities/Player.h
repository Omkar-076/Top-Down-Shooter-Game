#pragma once
#include<SDL.h>
#include"ShootRequest.h"
#include<array>
class Player {
	float px, py, dX, dY;
	float cPx, cPy;
	int pw, ph;
	float MdirX, MdirY;
	float speed;
	float length;
	bool wantsToShoot;
	float offsetX,offsetY;
	bool isAlive;
	ShootRequest shootRequest;
	std::array <SDL_Texture* , 8 > textures;
	float rotation;
	enum Direction {
		RIGHT,
		UP_RIGHT,
		UP,
		UP_LEFT,
		LEFT,
		DOWN_LEFT,
		DOWN,
		DOWN_RIGHT
	};
	Direction direction;
public:
	SDL_Rect rect;
	void setTextures(const std::array<SDL_Texture*, 8>& textures);
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