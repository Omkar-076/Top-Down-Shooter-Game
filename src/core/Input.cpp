#include "Input.h"
#include<SDL.h>
#include<SDL_ttf.h>
void Input::handleInput(bool& running) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			running = false;
		}
	}
}