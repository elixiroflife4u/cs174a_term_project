#ifndef SOUND_PLAYER_H
#define SOUND_PLAYER_H

#include <string>

/** The SoundPlayer namespace contains the entire interface
  * to the SoundPlayer subsystem. It can play a background
  * song as well as mix in one channel of sound effects.
  *
  * All functions check to see if the subsystem is initialized.
  * It is okay to call any function even if it is not.
  *
  * The SoundPlayer subsystem uses SDL and SDL_mixer.
  */
namespace SoundPlayer {
	/** Initializes the subsystem. Must be called before
	  * using any other functions.
	  * @return True if successful.
	  */
	bool init();
	/** Unloads the SoundPlayer subsystem.
	  * You must call init() again to use any other
	  * functions again.
	  */
	void quit();

	/** Plays a background song, stopping the previous one
	  * if applicable. By default, the song is played in a
	  * continuous loop. The background song is not cached;
	  * calling this function always causes the song to
	  * be loaded from disk.
	  *
	  * The file type may be WAVE, MOD, MIDI, OGG, MP3, or FLAC.
	  * Please don't use MOD or MIDI; I have a feeling they won't
	  * work well, but you can certainly try.
	  * 
	  * @param path Path to the song.
	  * @param loop Loop count. -1 for infinite loop. 0 for no play.
	  */
	bool playBackground(const char* path, int loop = -1);
	/** Stops the background song, if applicable. */
	void stopBackground();

	/** Loads a sound effect file into the cache, but does
	  * not play it. Since loading a file on-demand may cause
	  * a small delay the first time, it is suggested that you
	  * load sounds before you attempt to play it.
	  *
	  * The file type may be WAVE, AIFF, RIFF, OGG, or VOC.
	  *
	  * @param Path to sound file.
	  * @return True on success.
	  */
	bool loadSound(const std::string& path);
	/** Plays a sound effect file immediately. The sound
	  * file is cached into memory. However, if it does not
	  * exist in the cache, it will first be loaded off disk.
	  * To avoid any delays loading the file on first use, it
	  * is suggested that you preload all sound files with
	  * loadSound().
	  *
	  * @param path Path to sound file.
	  * @param loop Loop count. 0 for infinite loop. NOTE:
	  *  This is different than the loop count for playBackground().
	  */
	bool playSound(const std::string& path, int loop = 1);
	/** Stops a sound effect, if applicable. */
	void stopSound();
}

/** The SoundPlayerGuard class simply automates the initialization
  * and unloading of the SoundPlayer subsystem. Simply instantiate
  * an object in automatic storage, and the subsystem will stay
  * alive for the life of the object. Upon destruction, the subsystem
  * will be uninitialized. For example:
@code
int main() {
	SoundPlayerGuard spg;
	if(spg.initialized) {
		SoundPlayer::playBackground("test.mp3");
	} else {
		std::cerr<<"SoundPlayer failed to initialize.\n";
	}
}
@endcode
  */
class SoundPlayerGuard {
public:
	/** Initializes the SoundPlayer subsystem. */
	SoundPlayerGuard() : initialized(SoundPlayer::init()) {}
	/** Unloads the SoundPlayer subsystem. */
	~SoundPlayerGuard() { if(initialized) SoundPlayer::quit(); }
	const bool initialized; ///< True if initialization succeeded.
};

#endif