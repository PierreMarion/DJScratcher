#pragma once
#include "fmod\fmod.hpp"
#include "fmod\fmod_errors.h"
#include <iostream>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
using namespace std;
class Player
{
public:
	Player();
	~Player();
	void Load();
	void Play();

	void SetSampleSize(int newSize);
	FMOD::System* GetFmodSys();
	void AddChannelToMaster(FMOD::Channel* newChannel);

	FMOD::Channel* channel;
	FMOD::Sound* currentSound;
	float *spec;
	bool ChangeVolume(double nVolume, bool bScalar);

private:
	FMOD::System *FMODsys;
	FMOD_RESULT result;
	FMOD::ChannelGroup* masterSound;
	int sampleSize;
	bool change;
	void frequencyAnalysis();

	void FMODErrorCheck(FMOD_RESULT result);

	void InitSpec();
};