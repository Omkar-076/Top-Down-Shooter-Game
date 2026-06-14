#include"Collision.h"
#include<iostream>
bool Collision::isColliding(SDL_Rect rect1, SDL_Rect rect2){
	if ((rect1.x <= (rect2.x + rect2.w)) && ((rect1.x + rect1.w) >= rect2.x)) {
		if(((rect1.y + rect1.h) >= rect2.y) && (rect1.y <= (rect2.y + rect2.h))){
			std::cout << "Thoka"<<std::endl;
			return true;
		}
	}
	return false;
}