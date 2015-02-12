#include "FileManagement.h"

using namespace boost::filesystem;

FileManagement::FileManagement(void)
{

}


FileManagement::~FileManagement(void)
{

}

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

string FileManagement::addSongInComboBox(string fileNames, vector<sf::String> songList, int songSeperatorIndex)
{
	string song = fileNames.substr(0, songSeperatorIndex);

	if(std::find(songList.begin(), songList.end(), song) == songList.end())
	{
		return song;
	}
	return "";
	
}
