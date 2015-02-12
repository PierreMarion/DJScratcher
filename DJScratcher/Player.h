#pragma once
#include "fmod\fmod.hpp"
#include "fmod\fmod_errors.h"
#include <iostream>
#include "Song.h"

using namespace std;

class Player
{
public:
	Player();
	~Player();
	void Load(string songName);
	void Play();
	void Stop();
	void Pause(bool pause);
	std::string getArtist();
	std::string getAlbum();
	void ChangeVolume(string nVolume);
	void BassEqModification(double bassFrequency);
	void MediumEqModification(double mediumFrequency);
	void TrebbleEqModification(double trebbleFrequency);
	void PitchModification(double pitchFrequency);
	void SpeedModification(float speedFrequency);
	void SetSampleSize(int newSize);
	FMOD::System* GetFmodSys();
	void AddChannelToMaster(FMOD::Channel* newChannel);

	FMOD::Channel* channel;
	FMOD::Sound* currentSound;
	float *spec;
	

private:
	FMOD::System *FMODsys;
	FMOD::ChannelGroup* masterSound;
	int sampleSize;
	bool change;
	float frequency;

	std::string songArtist;
	std::string songAlbum;

	void FMODErrorCheck(FMOD_RESULT result);
	FMOD::DSPConnection* eqBassConnection;
	FMOD::DSPConnection* eqMediumConnection;
	FMOD::DSPConnection* eqTrebbleConnection;
	FMOD::DSPConnection* eqPitchConnection;

	FMOD::DSP* dspBassEQ;
	FMOD::DSP* dspMedEQ;
	FMOD::DSP* dspTrebbleEQ;
	FMOD::DSP* dspPitchEQ;

	void InitSpec();
};