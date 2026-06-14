#pragma once
#include<SDL.h>
class Collision {
public:
	static bool isColliding(SDL_Rect rect1, SDL_Rect rect2);
};