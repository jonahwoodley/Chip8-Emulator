#include "audio_manager.hpp"


AudioManager::AudioManager() : audioDevice(0) {}


bool AudioManager::init() {

    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        std::cerr << "SDL could not initialize audio subsystem: " << SDL_GetError() << std::endl;
        return false;
    }

	SDL_AudioSpec desiredSpec;
	SDL_zero(desiredSpec);
	desiredSpec.freq = 44100;
	desiredSpec.format = AUDIO_U8;
	desiredSpec.channels = 1;
	desiredSpec.samples = 512;
	desiredSpec.callback = audioCallback;

	audioDevice = SDL_OpenAudioDevice(nullptr, 0, &desiredSpec, &audioSpec, 0);

	if (audioDevice == 0) {
		std::cerr << "Failed to open audio device: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void AudioManager::audioCallback(void* userdata, Uint8* stream, int len) {
    static int phase = 0;
    for (int i = 0; i < len; i++, phase++) {
        stream[i] = (phase % 200 < 100) ? 255 : 0;  
    }
}

void AudioManager::playSound() {
    SDL_PauseAudioDevice(audioDevice, 0); 
}

void AudioManager::stopSound() {
    SDL_PauseAudioDevice(audioDevice, 1); 
}


void AudioManager::cleanUp() {
    if (audioDevice != 0) {
        SDL_CloseAudioDevice(audioDevice);
        audioDevice = 0;
    }
}