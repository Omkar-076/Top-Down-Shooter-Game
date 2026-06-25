#include "Input.h"
#include<SDL.h>
#include<vector>
SDL_Event Input::event;
std::vector<Uint8> Input::lastKeystate;
Uint32 Input::currentMouseState = 0;
Uint32 Input::lastMouseState = 0;
const Uint8* Input::keystate = nullptr;
int Input::movement = None;
int Input::mx = 0;
int Input::my = 0;
bool Input::wantsToShoot = false;
int Input::keystateSize = 0;
void Input::init() {
	keystate = SDL_GetKeyboardState(&keystateSize);
	lastKeystate.resize(keystateSize);
}
void Input::handleInput(bool& running) {
	
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

	wantsToShoot = false;
	
	//Mouse Inputs
	lastMouseState = currentMouseState;
	currentMouseState = SDL_GetMouseState(&Input::mx, &Input::my);
	bool click = (((lastMouseState & SDL_BUTTON_LEFT) != true) && ((currentMouseState & SDL_BUTTON_LEFT) == true));
	if (click){
		wantsToShoot = true;
	}	
}

bool Input::keyPressed(SDL_Scancode key) {
	return (!lastKeystate[key] && keystate[key]);
}

void Input::endFrame() {
	for (int i = 0; i < keystateSize; i++) {
		lastKeystate[i] = keystate[i];
	}
}