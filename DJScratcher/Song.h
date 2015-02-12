#pragma once
#include <string>
#include "fmod.hpp"
#include "fmod_errors.h"
#include <iostream>
#include <id3/tag.h>
#include <id3\field.h>
#include <id3\id3lib_frame.h>
#include <id3.h>

class Song
{
	public:
		Song(std::string path, FMOD::System* FMODsys, bool sfx);
		~Song(void);

		void Play();
		void Load();
		void SetSongInfo();

		FMOD::Sound* GetSound();
		std::string getArtist();
		std::string getAlbum();
	
		FMOD::Channel* channel;

	private:
		FMOD::Sound* sound;
		FMOD::System* system;
		ID3_Tag* songTag;
		ID3_Field* songField;
		ID3_Frame* songFrame;
		std::string songArtist;
		std::string songAlbum;
		std::string path;
		bool sfx;
};

