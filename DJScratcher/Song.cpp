#include "Song.h"
/**
Class containing the logic behind what is, for our project, a song.
*/


/**
Constructor of a song
param path Access path to the song, in string format
param FMODSys FMOD::System to which the song will be linked
param sfx boolean checking if the new song is just an sound effect or a whole song
*/
Song::Song(std::string path, FMOD::System* FMODsys, bool sfx)
{
	system = FMODsys;

	this->path = path;
	this->songTag = new ID3_Tag(path.c_str());
	this->sfx = sfx;

	SetSongInfo();
	Load();
}

/**
Destructor of a song
*/
Song::~Song(void)
{
	if(!this->sfx)
	{
		this->sound->release();
	}
}
/**
Function allowing the program to get various informations on the song
*/
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
/**
Function sets the song as the currentSong on the linked FMOD::System 
*/
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

/**
function returning the FMOD::Sound of the song
return sound the song's FMOD::Sound
*/
FMOD::Sound* Song::GetSound()
{
	return this->sound;
}
/**
function returning the artist of the song
return songArtist the song's artist
*/
std::string Song::getArtist()
{
	return this->songArtist;
}
/**
function returning the name of the album of the song
return sound the song's album name
*/
std::string Song::getAlbum()
{
	return this->songAlbum;
}