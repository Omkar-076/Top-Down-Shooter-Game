#pragma once
#include<SDL.h>
#include<vector>
class Input {
	static SDL_Event event;
	static const Uint8* keystate;
	static std::vector<Uint8> lastKeystate;
	static Uint32 currentMouseState;
	static Uint32 lastMouseState;
	enum MoveState{	
		None = 0,
		Up = 1<<0,
		Right = 1<<1,
		Down = 1<<2,
		Left = 1<<3
	};
	static int keystateSize;
public:
	static bool toggleFullScreenPressed;
	static bool wantsToShoot;
	static int mx, my;
	static int movement;
	static void init();
	static void handleInput(bool&);
	static bool keyPressed(SDL_Scancode);
	static void endFrame();
};