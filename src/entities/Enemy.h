#pragma once
#include<SDL.h>
class Enemy {
	float ex, ey, ew, eh;
	float dirX, dirY,length;
	float speed;
	bool isAlive;
	int scoreValue;
	
	float rotation;
	int health;
	
public:
	enum EnemyType { NORMAL, TANK };
	EnemyType type;
	SDL_Rect rect;
	SDL_Rect hitbox;
	Enemy(float ex, float ey, float speed, EnemyType type );
	bool isDead();
	bool takeDamage();
	void markDead();
	void update(float deltaTime, float px, float py);
	void render(SDL_Renderer* renderer, SDL_Texture* texture);
	int getScoreValue();
};