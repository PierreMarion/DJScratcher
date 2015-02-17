#include "Player.h"
#include <string>
#include <stdlib.h>

using namespace std;
/**
Class controlling the audio system management of the application
*/

/**
Constructor of the audio system
*/
Player::Player()
{
	InitSpec();

	FMODErrorCheck(FMOD::System_Create(&FMODsys));
	FMODErrorCheck(FMODsys->init(100, FMOD_INIT_NORMAL, 0));

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
/**
Destructor of the audio system
*/
Player::~Player()
{
	delete[] spec;

	FMODsys->release();
	currentSound->release();
}
/**
Function that loads the current song and all of its informations
param songName Name of the song you want to load
*/
void Player::Load(string songName)
{
	this->change = false;
	songName.insert(0, "C:/Musique/");
	Song* newSong = new Song(songName, this->FMODsys, true);
	this->currentSound = newSong->GetSound();
	this->songArtist = newSong->getArtist();
	this->songAlbum = newSong->getAlbum();
	Play();
	delete newSong;
	this->FMODsys->update();
}
/**
Function playing the song in the application
*/
void Player::Play()
{
	FMODErrorCheck(FMODsys->playSound(FMOD_CHANNEL_FREE, this->currentSound, true, &this->channel));
	
	FMODErrorCheck(this->channel->setChannelGroup(masterSound));

	this->channel->setPaused(false);
	this->channel->setVolume(0.5f);
	this->FMODsys->update();
	channel->getFrequency(&frequency);
}
/**
Function returning the current song's artist name
return songArtist the name of the current song's artist
*/
std::string Player::getArtist()
{
	return this->songArtist;
}
/**
Function returning the current song's album name
return songArtist the name of the current song's album
*/
std::string Player::getAlbum()
{
	return this->songAlbum;
}

/**
Function needed in the constructor of a player, sets the specs of the player
*/
void Player::InitSpec()
{
	sampleSize = 256;
	spec = new float[sampleSize];
	for (int i = 0; i < sampleSize; i++)
	{
		spec[i] = 0;
	}
}
/**
FMOD's error checking function
*/
void Player::FMODErrorCheck(FMOD_RESULT result)
{
	if (result != FMOD_OK)
    {
        std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
		system("pause");
        exit(-1);
    }
}
/**
Function that manages the bass equalization with a new given frequency
param bassFrequency new frequency's value
*/
void Player::BassEqModification(double bassFrequency)
{
	dspBassEQ->setParameter(FMOD_DSP_PARAMEQ_GAIN, bassFrequency);
}
/**
Function that manages the medium equalization with a new given frequency
param mediumFrequency new frequency's value
*/
void Player::MediumEqModification(double mediumFrequency)
{
	dspMedEQ->setParameter(FMOD_DSP_PARAMEQ_GAIN, mediumFrequency);
}
/**
Function that manages the trebble equalization with a new given frequency
param trebbleFrequency new frequency's value
*/
void Player::TrebbleEqModification(double trebbleFrequency)
{
	dspTrebbleEQ->setParameter(FMOD_DSP_PARAMEQ_GAIN, trebbleFrequency);
}
/**
Function that manages the speed of the song with a new given frequency
param speedFrequency new frequency's value
*/
void Player::SpeedModification(float speedFrequency)
{
	channel->setFrequency(frequency * speedFrequency);
}
/**
Function that manages the pitch of the song with a new given frequency
param pitchFrequency new frequency's value
*/
void Player::PitchModification(double pitchFrequency)
{
	dspPitchEQ->setParameter(FMOD_DSP_PITCHSHIFT_PITCH, pitchFrequency);
}
/**
Function that manages the volume of the song with a given value
param nVolume new volume value
*/
void Player::ChangeVolume(string nVolume)
{
	float value = ::atof(nVolume.c_str());
	this->channel->setVolume(value);
}
/**
Function that pauses/unpause the song
param pause  value of the wanted pause, true if you want to pause, false if you want unpaused
*/
void Player::Pause(bool pause)
{
	this->channel->setPaused(pause);
}
/**
Function that stops the song
*/
void Player::Stop()
{
	this->channel->stop();
	this->change = true;
	this->FMODsys->update();
}