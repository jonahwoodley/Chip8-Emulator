#pragma once 

#include <SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

class RenderWindow {
public:
	RenderWindow(const char* title, int width, int height);

	void clear();
	void display();
	void cleanUp();

	SDL_Window* getWindow() const {return window;}
	SDL_Renderer* getRenderer() const {return renderer;}

	void renderGameDisplay(uint32_t* pixels, int displayWidth, int displayHeight);

	

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* sdlTexture;
	SDL_Rect calculateDisplayRect(int gameDisplayWidth, int gameDisplayHeight) const;
};