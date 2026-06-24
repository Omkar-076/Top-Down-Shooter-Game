#include "Input.h"
#include<SDL.h>
#include<iostream>
SDL_Event Input::event;
const Uint8* Input::lastKeystate = 0;
Uint32 Input::currentMouseState = 0;
Uint32 Input::lastMouseState = 0;
const Uint8* Input::keystate = 0;
int Input::movement = None;
int Input::mx = 0;
int Input::my = 0;
bool Input::wantsToShoot = false;
bool Input::wantsToRestart = false;
void Input::handleInput(bool& running) {
	lastKeystate = keystate;
	keystate = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			running = false;
		}
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				running = false;
			}
		}
	}
	movement = None;
	if (keystate[SDL_SCANCODE_W]){
		movement |= Up;
	}
	if (keystate[SDL_SCANCODE_A]) {
		movement |= Left;
	}
	if (keystate[SDL_SCANCODE_S]) {
		movement |= Down;
	}
	if (keystate[SDL_SCANCODE_D]) {
		movement |= Right;
	}

	wantsToRestart = false;
	if (!lastKeystate[SDL_SCANCODE_R] && keystate[SDL_SCANCODE_R]) {
		wantsToRestart = true;
	}

	wantsToShoot = false;
	
	//Mouse Inputs
	lastMouseState = currentMouseState;
	currentMouseState = SDL_GetMouseState(&Input::mx, &Input::my);
	bool click = (((lastMouseState & SDL_BUTTON_LEFT) != true) && ((currentMouseState & SDL_BUTTON_LEFT) == true));
	if (click){
		wantsToShoot = true;
	}
}