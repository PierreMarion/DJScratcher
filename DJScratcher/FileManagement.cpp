#include "FileManagement.h"

using namespace boost::filesystem;

/**
Class managing the files required to play music with our application
*/
/**
Constructor of the manager
*/
FileManagement::FileManagement(void)
{

}

/**
Destructor of the manager
*/
FileManagement::~FileManagement(void)
{

}
/**
Function returning the number of files in the given path
param directoryPath Given path in which are the files to manage
return counter the amount of files
*/
int FileManagement::getFileCount(string directoryPath)
{
	path directory(directoryPath);
	int counter = 0;

	for(directory_iterator it(directory); it != directory_iterator(); ++it)
	{
		counter++;
	}

	return counter;
}
/**
Function returning the name of every files in the given path
param directoryPath Given path in which are the files to manage
return fileNames the name of every files separated by coma (,)
*/
string FileManagement::getFileNames(string directoryPath)
{
	path directory(directoryPath);
	string fileNames = "";

	for(directory_iterator it(directory); it != directory_iterator(); ++it)
	{
		fileNames += it->path().filename().string();
		fileNames += ", ";
	}

	return fileNames;
}
/**
Function adding a new file to the list of the application
param fileNames List of every files in a given path
param songList List of every songs in the application
param songSeperatorIndex Index of the new file in fileNames
return song the new file which is either nothing or a new song
*/
string FileManagement::addSongInComboBox(string fileNames, vector<sf::String> songList, int songSeperatorIndex)
{
	string song = fileNames.substr(0, songSeperatorIndex);

	if(std::find(songList.begin(), songList.end(), song) == songList.end())
	{
		return song;
	}
	return "";
	
}
