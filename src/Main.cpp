// Top-Down Shooter Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
#define SDL_MAIN_HANDLED
#include<iostream>
#include "core/Game.h"

int main(){
	Game game;
	game.init();
	game.run();
	return 0;
}
