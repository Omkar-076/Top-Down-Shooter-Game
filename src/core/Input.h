#pragma once
#include<SDL.h>
class Input {
	static SDL_Event event;
	static const Uint8* keystate;
	enum MoveState{	
		None = 0,
		Up = 1<<0,
		Right = 1<<1,
		Down = 1<<2,
		Left = 1<<3
	};
public:
	static int movement;
	static void handleInput(bool&);
};