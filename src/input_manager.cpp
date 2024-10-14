#include "input_manager.hpp"

void InputManager::handleInput(Chip8& chip8, SDL_Event& event, bool& running) {
	if (event.type == SDL_QUIT) {
		running = false;
	}

    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_ESCAPE)
            exit(0);

        for (int i = 0; i < 16; ++i) {
            if (event.key.keysym.sym == keymap[i]) {
                chip8.key[i] = 1;
            }
        }
    }

    if (event.type == SDL_KEYUP) {
        for (int i = 0; i < 16; ++i) {
            if (event.key.keysym.sym == keymap[i]) {
                chip8.key[i] = 0;
            }
        }
    }
}