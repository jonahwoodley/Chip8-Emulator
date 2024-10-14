#pragma once 

#include "render_window.hpp"
#include <SDL.h>

class ImGuiHelper {
public:
	static void init(RenderWindow& window);
	static void beginFrame();
	static void endFrame(RenderWindow& window);
	static void processEvent(SDL_Event* event);
	static void cleanUp();
};