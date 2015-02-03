#include "SoundSystem.h"

SoundSystem::SoundSystem()
{
	if (FMOD::System_Create(&_system) != FMOD_OK)
	{
		// Report Error
		return;
	}

	int driverCount = 0;
	_system->getNumDrivers(&driverCount);

	if (driverCount == 0)
	{
		// Report Error
		return;
	}

	// Initialize our Instance with 36 Channels
	_system->init(36, FMOD_INIT_NORMAL, nullptr);
}


SoundSystem::~SoundSystem()
{

}

void SoundSystem::createSound(FMOD::Sound* pSound, const char* pFile)
{
	_system->createSound(pFile, FMOD_DEFAULT, 0, &pSound);
}

void SoundSystem::playSoundd(FMOD::Sound* pSound, bool bLoop = false)
{
	//FMOD::ChannelGroup* channelGroup = new FMOD::ChannelGroup();
	if (!bLoop)
		pSound->setMode(FMOD_LOOP_OFF);
	else
	{
		pSound->setMode(FMOD_LOOP_NORMAL);
		pSound->setLoopCount(-1);
	}
	//_system->playSound(soundSystem, FMOD_CHANNELGROUP, false, 0);
	//_system->playSound(pSound, channelGroup, false, 0);
}

void SoundSystem::releaseSound(FMOD::Sound* pSound)
{
	pSound->release();
}