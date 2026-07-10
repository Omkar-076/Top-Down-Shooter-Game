#pragma once
#include<SDL.h>
class Enemy {
	float ex, ey, ew, eh;
	float dirX, dirY,length;
	float speed;
	bool isAlive;
	int scoreValue;
	enum Type {NORMAL};
	Type EnemyType;
	float rotation;
	
public:
	SDL_Rect rect;
	Enemy(float ex, float ey, float speed);
	bool isDead();
	void markDead();
	void update(float deltaTime, float px, float py);
	void render(SDL_Renderer* renderer, SDL_Texture* texture);
	int getScoreValue();
};