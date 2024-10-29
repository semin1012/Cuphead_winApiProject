#pragma once
#include <fmod.h>
#include <fmod_errors.h>

#define SOUND_MAX 1.0f
#define SOUND_MIN 0.0f
#define SOUND_DEFAULT 0.5f
#define SOUND_WEIGHT 0.01f

class Sound
{
	static FMOD_SYSTEM* gSoundSystem;
	FMOD_SOUND*  sound;
	FMOD_CHANNEL* channel;

	float volume;
	FMOD_BOOL fmodBool;
public:
	Sound(const char* path, bool loop);
	~Sound();

	static void	Init();
	static void	Release();
	void			play();
	void			pause();
	void			resume();
	void			stop();
	void			volumeUp();
	void			volumeDown();
	void			SetVolume(float volume);
	void			Update();
};

