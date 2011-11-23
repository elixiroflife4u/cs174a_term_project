#include "SoundPlayer.h"
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include <map>

static bool initialized = false;

static Mix_Music* background = NULL;

typedef std::map<std::string, Mix_Chunk*> ChunkMap;
static ChunkMap chunks;
static Mix_Chunk* fetchSound(const std::string& path) {
	if(!initialized) return false;

	Mix_Chunk* sound = chunks[path];
	if(sound)
		return sound;

	sound = Mix_LoadWAV(path.c_str());
	if(!sound)
		return NULL;

	chunks[path] = sound;
	return sound;
}

static int soundChannel = -1;

namespace SoundPlayer {
	bool init() {
		SDL_Init(SDL_INIT_AUDIO);

		if(Mix_OpenAudio(22050, AUDIO_S16, 2, 4096))
			return false;
		initialized = true;
		return true;
	}

	void quit() {
		if(!initialized) return;

		stopBackground(); //stop and unload background
		stopSound(); //stop (but doesn't unload) sound effect

		//Unload all loaded sound effects
		for(ChunkMap::const_iterator i = chunks.begin(); i != chunks.end(); ++i)
			Mix_FreeChunk(i->second);
		chunks.clear();

		///< need these two to be disabled otherwise the release verion of code fails here(debug works fines).
		Mix_CloseAudio();   
		SDL_Quit();
	}

	bool playBackground(const char* path, int loop) {
		if(!initialized) return false;

		stopBackground();
		background = Mix_LoadMUS(path);
		if(!background)
			return false;
		Mix_PlayMusic(background, loop);
		return true;
	}

	void stopBackground() {
		if(background) {
			Mix_HaltMusic();
			Mix_FreeMusic(background);
			background = NULL;
		}
	}

	bool loadSound(const std::string& path) {
		if(!initialized) return false;

		//Don't reload an already opened file
		if(chunks[path])
			return false;
		return fetchSound(path);
	}

	bool playSound(const std::string& path, int loop) {
		stopSound();

		Mix_Chunk* sound = fetchSound(path);
		if(!sound)
			return false;
		soundChannel = Mix_PlayChannel(-1, sound, loop - 1);
		return true;
	}

	void stopSound() {
		if(soundChannel >= 0) {
			Mix_HaltChannel(soundChannel);
			soundChannel = -1;
		}
	}
}