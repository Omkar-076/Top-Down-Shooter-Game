#include "Input.h"
#include<SDL.h>
SDL_Event Input::event;
const Uint8* Input::keystate = nullptr;
int Input::movement = None;
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
}