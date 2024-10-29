#include "Sound.h"

FMOD_SYSTEM* Sound::gSoundSystem;

Sound::Sound(const char* path, bool loop)
{
	if (loop) 
		FMOD_System_CreateSound(gSoundSystem, path, FMOD_LOOP_NORMAL, 0, &sound);
	else
		FMOD_System_CreateSound(gSoundSystem, path, FMOD_DEFAULT, 0, &sound);
	channel = nullptr;
	volume = SOUND_DEFAULT;
}

Sound::~Sound()
{
	FMOD_Sound_Release(sound);
}

void Sound::Init()
{
	FMOD_System_Create(&gSoundSystem, FMOD_VERSION);
	FMOD_System_Init(gSoundSystem, 32, FMOD_INIT_NORMAL, nullptr);
}

void Sound::Release()
{
	FMOD_System_Close(gSoundSystem);
	FMOD_System_Release(gSoundSystem);
}

void Sound::play()
{
	FMOD_System_PlaySound(gSoundSystem, sound, nullptr, false, &channel);
}

void Sound::pause()
{
	FMOD_Channel_SetPaused(channel, true);
}

void Sound::resume()
{
	FMOD_Channel_SetPaused(channel, false);
}

void Sound::stop()
{
	FMOD_Channel_Stop(channel);
}

void Sound::volumeUp()
{
	if (volume < SOUND_MAX)
		volume += SOUND_WEIGHT;
	FMOD_Channel_SetVolume(channel, volume);
}

void Sound::volumeDown()
{
	if (volume > SOUND_MIN)
		volume -= SOUND_WEIGHT;
	FMOD_Channel_SetVolume(channel, volume);
}

void Sound::SetVolume(float volume)
{
	this->volume = volume;
	if (this->volume > SOUND_MAX)
		this->volume = SOUND_MAX;
	if (this->volume < SOUND_MIN)
		this->volume = SOUND_MIN;
	FMOD_Channel_SetVolume(channel, this->volume);
}

void Sound::Update()
{
	FMOD_Channel_IsPlaying(channel, &fmodBool);
	if (fmodBool) 
		FMOD_System_Update(gSoundSystem);
}
