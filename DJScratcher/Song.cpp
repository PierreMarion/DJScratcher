#include "Song.h"

//Tout viens de Ferland.


Song::Song(std::string path, FMOD::System* FMODsys, bool sfx)
{
	system = FMODsys;

	this->path = path;
	this->songTag = new ID3_Tag(path.c_str());
	this->sfx = sfx;

	SetSongInfo();
	Load();
}


Song::~Song(void)
{
	if(!this->sfx)
	{
		this->sound->release();
	}
}

void Song::SetSongInfo()
{
	this->songFrame = songTag->Find(ID3FID_BAND);
	char artist[1024];
    songFrame->Field(ID3FN_TEXT).Get(artist, 1024);
	this->songArtist = artist;

	this->songFrame = songTag->Find(ID3FID_ALBUM);
	char album[1024];
    songFrame->Field(ID3FN_TEXT).Get(album, 1024);
	this->songAlbum = album;
}

void Song::Load()
{
	FMOD_RESULT result;
	result = system->createStream(this->path.c_str(), FMOD_SOFTWARE | FMOD_CREATECOMPRESSEDSAMPLE, 0, &sound);

	if (result != FMOD_OK)
	{
		std::cout << "FMOD error! (%d) %s\n" << result;
		exit(-1);
	}
}

void Song::Play()
{
	system->playSound(FMOD_CHANNEL_FREE, sound, false, &this->channel);
}

FMOD::Sound* Song::GetSound()
{
	return this->sound;
}

std::string Song::getArtist()
{
	return this->songArtist;
}

std::string Song::getAlbum()
{
	return this->songAlbum;
}