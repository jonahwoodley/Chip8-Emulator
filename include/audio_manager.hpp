#pragma once

#include <SDL.h>
#include <iostream>

class AudioManager {
public:
	AudioManager();
	bool init();
	void playSound();
	void stopSound();
	void cleanUp();

private:
	SDL_AudioDeviceID audioDevice;
	SDL_AudioSpec audioSpec;

	static void audioCallback(void* userdata, Uint8* stream, int len);
};