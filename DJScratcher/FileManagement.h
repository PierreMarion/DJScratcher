#pragma once
#include <string>
#include "TGUI\TGUI.hpp"
#include <boost\filesystem.hpp>

using namespace std;

class FileManagement
{
public:
	FileManagement(void);
	~FileManagement(void);
	int getFileCount(string directoryPath);
	string getFileNames(string directoryPath);
	string addSongInComboBox(string fileNames, vector<sf::String> songList, int songSeperatorIndex);

};

