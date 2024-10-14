#include <iostream>

#include "render_window.hpp"

RenderWindow::RenderWindow(const char* title, int width, int height) {
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (!window) {
		SDL_Log("Window could not be created. SDL_Error: %s",SDL_GetError());
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		SDL_Log("Renderer could not be created. SDL_Error: %s",SDL_GetError());
	}

    sdlTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 64, 32);
    if (!sdlTexture) {
        SDL_Log("Texture could not be created. SDL_Error: %s", SDL_GetError());
    }

}

SDL_Rect RenderWindow::calculateDisplayRect(int gameDisplayWidth, int gameDisplayHeight) const {
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    int xPos = (windowWidth - gameDisplayWidth) / 2;
    int yPos = (windowHeight - gameDisplayHeight) / 2;

    return SDL_Rect{xPos, yPos, gameDisplayWidth, gameDisplayHeight};
}

void RenderWindow::renderGameDisplay(uint32_t* pixels, int displayWidth, int displayHeight) {
    SDL_Rect destRect = calculateDisplayRect(displayWidth, displayHeight);

    SDL_SetRenderDrawColor(renderer, 255, 182, 193, 255);
    SDL_RenderClear(renderer); 

	if (SDL_UpdateTexture(sdlTexture, NULL, pixels, 64 * sizeof(uint32_t)) != 0) {
	    std::cerr << "Failed to update texture! SDL_Error: " << SDL_GetError() << std::endl;
	    return;
	}

	if (SDL_RenderCopy(renderer, sdlTexture, NULL, &destRect) != 0) {
	    std::cerr << "Failed to copy texture to renderer! SDL_Error: " << SDL_GetError() << std::endl;
	    return;
	}

	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);

    SDL_RenderPresent(renderer);

}


void RenderWindow::clear() {
	SDL_RenderClear(renderer);
}

void RenderWindow::cleanUp() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}