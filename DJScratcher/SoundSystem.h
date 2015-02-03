#pragma once
#include "fmod\fmod.hpp"
#include "fmod\fmod_errors.h"

class SoundSystem
{
	FMOD::System* _system;
public:
	SoundSystem();
	~SoundSystem();
	void createSound(FMOD::Sound* pSound, const char* pFile);
	void playSoundd(FMOD::Sound* pSound, bool bLoop);
	void releaseSound(FMOD::Sound* pSound);
};

