#include "Player.h"
#include <string>
#include <stdlib.h>

using namespace std;

Player::Player()
{
	InitSpec();

	result = FMOD::System_Create(&FMODsys);
	FMODErrorCheck(result);
	FMODErrorCheck(result = FMODsys->init(100, FMOD_INIT_NORMAL, 0));

	FMODErrorCheck(this->FMODsys->createChannelGroup(NULL, &this->masterSound));

	FMODErrorCheck(this->FMODsys->createDSPByType(FMOD_DSP_TYPE_PARAMEQ, &dspBassEQ));
	dspBassEQ->setParameter(FMOD_DSP_PARAMEQ_CENTER, 1000);
	dspBassEQ->setParameter(FMOD_DSP_PARAMEQ_BANDWIDTH, 0.2);

	FMODErrorCheck(this->FMODsys->createDSPByType(FMOD_DSP_TYPE_PARAMEQ, &dspMedEQ));

	FMODErrorCheck(this->FMODsys->createDSPByType(FMOD_DSP_TYPE_PARAMEQ, &dspTrebbleEQ));
	dspTrebbleEQ->setParameter(FMOD_DSP_PARAMEQ_CENTER, 15000);
	dspTrebbleEQ->setParameter(FMOD_DSP_PARAMEQ_BANDWIDTH, 5);
	
	FMODErrorCheck(this->FMODsys->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dspPitchEQ));
	
	FMODsys->addDSP(dspBassEQ, &eqBassConnection);
	FMODsys->addDSP(dspMedEQ, &eqMediumConnection);
	FMODsys->addDSP(dspTrebbleEQ, &eqTrebbleConnection);
	FMODsys->addDSP(dspPitchEQ, &eqPitchConnection);

	FMODsys->update();
}
Player::~Player()
{
	delete[] spec;

	FMODsys->release();
	currentSound->release();
}

void Player::Load(string songName)
{
	this->change = false;
	songName.insert(0, "songs/");
	Song* newSong = new Song(songName, this->FMODsys, true);
	this->currentSound = newSong->GetSound();
	this->songArtist = newSong->getArtist();
	this->songAlbum = newSong->getAlbum();
	Play();
	delete newSong;
	this->FMODsys->update();
}

void Player::Play()
{
	FMODErrorCheck(FMODsys->playSound(FMOD_CHANNEL_FREE, this->currentSound, true, &this->channel));
	
	FMODErrorCheck(this->channel->setChannelGroup(masterSound));

	this->channel->setPaused(false);
	this->channel->setVolume(0.5f);
	this->FMODsys->update();
	channel->getFrequency(&frequency);
}

std::string Player::getArtist()
{
	return this->songArtist;
}

std::string Player::getAlbum()
{
	return this->songAlbum;
}

void Player::frequencyAnalysis()
{
	this->change = false;
	bool isPlaying = true;
	bool paused = false;
	bool firstTime = true;
	float *specLeft;
	float *specRight;

	while(true)
	{
		if(this->channel->getPaused(&paused) == FMOD_OK && !paused)
		{
			FMODsys->update();	

			specLeft = new float[sampleSize];
			specRight = new float[sampleSize];

			this->masterSound->getSpectrum(specLeft, sampleSize, 0, FMOD_DSP_FFT_WINDOW_RECT);
			this->masterSound->getSpectrum(specRight, sampleSize, 1, FMOD_DSP_FFT_WINDOW_RECT);

			for (int i = 0; i < sampleSize; i++)
			{
				spec[i] = (specLeft[i] + specRight[i]) / 2;
			}

			float hzRange = (44100 / 2) / static_cast<float>(sampleSize);
			
			delete[] specLeft;
			delete[] specRight;
		}

		if(change)
		{
			break;
		}
	}
	this->channel->stop();
}
void Player::InitSpec()
{
	sampleSize = 256;
	spec = new float[sampleSize];
	for (int i = 0; i < sampleSize; i++)
	{
		spec[i] = 0;
	}
}

void Player::FMODErrorCheck(FMOD_RESULT result)
{
	if (result != FMOD_OK)
    {
        std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
		system("pause");
        exit(-1);
    }
}

void Player::BassEqModification(double bassFrequency)
{
	dspBassEQ->setParameter(FMOD_DSP_PARAMEQ_GAIN, bassFrequency);
}
void Player::MediumEqModification(double mediumFrequency)
{
	dspMedEQ->setParameter(FMOD_DSP_PARAMEQ_GAIN, mediumFrequency);
}
void Player::TrebbleEqModification(double trebbleFrequency)
{
	dspTrebbleEQ->setParameter(FMOD_DSP_PARAMEQ_GAIN, trebbleFrequency);
}
void Player::SpeedModification(float speedFrequency)
{
	channel->setFrequency(frequency * speedFrequency);
}
void Player::PitchModification(double pitchFrequency)
{
	dspPitchEQ->setParameter(FMOD_DSP_PITCHSHIFT_PITCH, pitchFrequency);
}

void Player::ChangeVolume(string nVolume)
{
	float value = ::atof(nVolume.c_str());
	this->channel->setVolume(value);
}

void Player::Pause(bool pause)
{
	this->channel->setPaused(pause);
}

void Player::Stop()
{
	this->channel->stop();
	this->change = true;
	this->FMODsys->update();
}