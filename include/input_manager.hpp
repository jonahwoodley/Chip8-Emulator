#pragma once

#include <SDL2/SDL.h>
#include "chip8.hpp"

class InputManager{
public:
	void handleInput(Chip8& chip8, SDL_Event& event, bool& running);

private:
    uint8_t keymap[16] = {
        SDLK_x, SDLK_1, SDLK_2, SDLK_3, SDLK_q, SDLK_w, SDLK_e, 
        SDLK_a, SDLK_s, SDLK_d, SDLK_z, SDLK_c, SDLK_4, SDLK_r, 
        SDLK_f, SDLK_v
    };
};