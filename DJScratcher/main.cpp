#include "TGUI\TGUI.hpp"
#include "Player.h"
#include "FileManagement.h"
#include "UIBuilder.h"
#include <algorithm>
#include <stdlib.h>

int main()
{
	bool playing = false;
	bool pause = false;
	
	FileManagement* fileManage = new FileManagement();
	UIBuilder* uiBuilder = new UIBuilder();
	Player* player = new Player();

	int fileCount = fileManage->getFileCount("songs/");

	sf::RenderWindow window(sf::VideoMode(1000, 800), "DjScratcher");
	tgui::Gui gui = tgui::Gui(window);
	gui.setGlobalFont("TGUI/fonts/DejaVuSans.ttf");

	tgui::Picture::Ptr backgroundImage(gui);
	backgroundImage->load("imgs/djEQ.png");
	backgroundImage->setSize(1000, 500);
	backgroundImage->setPosition(0, 300);

	tgui::ComboBox::Ptr songList(gui);
	uiBuilder->createComboBox(songList, "Black", 650, 150);

	//////////////LABELS///////////////////
	tgui::Label::Ptr listeningLabel(gui);
	uiBuilder->createLabel(listeningLabel, "White", "À l'écoute: ", 100, 35);

	tgui::Label::Ptr artistLabel(gui);
	uiBuilder->createLabel(artistLabel, "White", "Artiste: ", 200, 80);
	artistLabel->setTextSize(15);

	tgui::Label::Ptr albumLabel(gui);
	uiBuilder->createLabel(albumLabel, "White", "Album: ", 200, 110);
	albumLabel->setTextSize(15);

	tgui::Label::Ptr bassLabel(gui);
	uiBuilder->createLabel(bassLabel, "White", "Basse", 90, 150);

	tgui::Label::Ptr mediumLabel(gui);
	uiBuilder->createLabel(mediumLabel, "White", "Medium", 90, 250);

	tgui::Label::Ptr trebbleLabel(gui);
	uiBuilder->createLabel(trebbleLabel, "White", "Aigue", 90, 350);

	tgui::Label::Ptr speedLabel(gui);
	uiBuilder->createLabel(speedLabel, "White", "Vitesse", 90, 450);

	tgui::Label::Ptr pitchLabel(gui);
	uiBuilder->createLabel(pitchLabel, "White", "Tonalité", 90, 550);

	tgui::Label::Ptr volumeLabel(gui);
	uiBuilder->createLabel(volumeLabel, "White", "Volume", 410, 550);

	//////////////BUTTONS///////////////////
	tgui::Button::Ptr playButton(gui);
	uiBuilder->createButton(playButton, "Black", "Jouer", 700, 280);

	tgui::Button::Ptr stopButton(gui);
	uiBuilder->createButton(stopButton, "Black", "Arrêt", 700, 350);

	tgui::Button::Ptr nextButton(gui);
	uiBuilder->createButton(nextButton, "White", "Prochain", 830, 320);

	tgui::Button::Ptr backButton(gui);
	uiBuilder->createButton(backButton, "White", "Précedent", 580, 320);

	tgui::Button::Ptr updateButton(gui);
	uiBuilder->createButton(updateButton, "Black", "Rafraichir la liste", 850, 110);

	tgui::Button::Ptr randomSongButton(gui);
	uiBuilder->createButton(randomSongButton, "Black", "Chanson aléatoire", 650, 525);
	randomSongButton->setSize(200, 50);

	tgui::Button::Ptr resetSlidersButton(gui);
	uiBuilder->createButton(resetSlidersButton, "Black", "Réinitialiser les égalisateurs", 650, 600);
	resetSlidersButton->setSize(200, 50);

	//////////////SLIDERS///////////////////

	tgui::Slider::Ptr volSlider(gui);
	uiBuilder->createSlider(volSlider, "BabyBlue", 460, 250, 100, 0, 50);
	volSlider->setVerticalScroll(true);

	tgui::Slider::Ptr bassSlider(gui);
	uiBuilder->createSlider(bassSlider, "White", 100, 200, 300, 5, 100);

	tgui::Slider::Ptr mediumSlider(gui);
	uiBuilder->createSlider(mediumSlider, "White", 100, 300, 300, 5, 100);

	tgui::Slider::Ptr trebbleSlider(gui);
	uiBuilder->createSlider(trebbleSlider, "White", 100, 400, 300, 5, 100);

	tgui::Slider::Ptr speedSlider(gui);
	uiBuilder->createSlider(speedSlider, "White", 100, 500, 15, 5, 10);

	tgui::Slider::Ptr pitchSlider(gui);
	uiBuilder->createSlider(pitchSlider, "White", 100, 600, 20, 5, 10);

	string fileNames = fileManage->getFileNames("songs/");
	for(int i = 0; i < fileNames.length(); i++) 
	{
		int songSeperatorIndex = fileNames.find(",");
		songList->addItem(fileManage->addSongInComboBox(fileNames, songList->getItems(), songSeperatorIndex));
		fileNames.erase(0, songSeperatorIndex + 2);
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			// Pass the event to all the widgets (if there would be widgets)
			gui.handleEvent(event);
		}

		tgui::Callback callback;
		while (gui.pollCallback(callback))
		{
			if (callback.id == 1) //Play
			{
				if(playing == false && pause == false)
				{
					if(songList->getSelectedItemIndex() == -1)
					{
						songList->setSelectedItem(0);
					}

					string songName = songList->getSelectedItem();
					player->Load(songName);
					playing = true;
					playButton->setText("Pause");
					listeningLabel->setText("À l'écoute: " + songName.substr(0, songName.length() - 4));
					artistLabel->setText("Artiste: " + player->getArtist());
					albumLabel->setText("Album: " + player->getAlbum());
				}
				else if(playing == true && pause == true)
				{
					player->Pause(false);
					pause = false;
					playButton->setText("Pause");
				}
				else if(playing == true && pause == false) 
				{
					player->Pause(true);
					pause = true;
					playButton->setText("Jouer");
				}
			}
			if(callback.id == 2) //stop
			{
				player->Stop();
				playButton->setText("Jouer");
				listeningLabel->setText("À l'écoute:");
				artistLabel->setText("Artiste: ");
				albumLabel->setText("Album: ");
				playing = false;
				pause = false;

				uiBuilder->resetSliders(bassSlider, mediumSlider, trebbleSlider, speedSlider, pitchSlider);
			}

			if(callback.id == 3) //Next
			{
				player->Stop();
				playing = false;
				pause = false;

				if(songList->getSelectedItemIndex() == fileCount - 1 || songList->getSelectedItemIndex() == -1)
				{
					songList->setSelectedItem(0);
				}
				else
				{
					songList->setSelectedItem(songList->getSelectedItemIndex() + 1);
				}
				

				string songName = songList->getSelectedItem();
				player->Load(songName);
				playing = true;
				playButton->setText("Pause");
				listeningLabel->setText("À l'écoute: " + songName.substr(0, songName.length() - 4));
				artistLabel->setText("Artiste: " + player->getArtist());
				albumLabel->setText("Album: " + player->getAlbum());

				uiBuilder->resetSliders(bassSlider, mediumSlider, trebbleSlider, speedSlider, pitchSlider);
				
			}

			if(callback.id == 4) //Back
			{
				player->Stop();
				playing = false;
				pause = false;

				if(songList->getSelectedItemIndex() == -1 || songList->getSelectedItemIndex() == 0)
				{
					songList->setSelectedItem(fileCount - 1);
				}
				else
				{
					songList->setSelectedItem(songList->getSelectedItemIndex() - 1);
				}
				
				string songName = songList->getSelectedItem();
				player->Load(songName);
				playing = true;
				playButton->setText("Pause");
				listeningLabel->setText("À l'écoute: " + songName.substr(0, songName.length() - 4));
				artistLabel->setText("Artiste: " + player->getArtist());
				albumLabel->setText("Album: " + player->getAlbum());

				uiBuilder->resetSliders(bassSlider, mediumSlider, trebbleSlider, speedSlider, pitchSlider);
				
			}
			if (callback.id == 5) //Update 
			{
				string fileNames = fileManage->getFileNames("songs/");

				if(fileManage->getFileCount("songs/") < fileCount)
				{
					songList->removeAllItems();
					fileCount = 0;
				}

				if(fileManage->getFileCount("songs/") > fileCount)
				{
					for(int i = 0; i < fileNames.length(); i++) 
					{
						int songSeperatorIndex = fileNames.find(",");

						string songCheck = fileManage->addSongInComboBox(fileNames, songList->getItems(), songSeperatorIndex);

						if(songCheck != "")
						{
							songList->addItem(songCheck);
						}

						fileNames.erase(0, songSeperatorIndex + 2);
					}

					fileCount = fileManage->getFileCount("songs/");
				}
			}

			if(callback.id == 6)  //random Song
			{
				int songIndex = rand() % fileCount;
				songList->setSelectedItem(songIndex);
			}

			if(callback.id == 7)
			{
				uiBuilder->resetSliders(bassSlider, mediumSlider, trebbleSlider, speedSlider, pitchSlider);
			}

			if(callback.id == 8) //Volume
			{
				string value = std::to_string(volSlider->getValue());

				if(value.length() == 1)
				{
					value.insert(0, "0");
				}
				if(value != "100")
				{
					value.insert(0, "0.");
				}
				else
				{
					value = "1.0";
				}
				player->ChangeVolume(value);
			}

			if(callback.id == 9) //BasseSlider
			{
				string value = std::to_string(bassSlider->getValue());
				double gain = ::strtod(value.c_str(), NULL);
				gain = gain / 100;
				player->BassEqModification(gain);
			}

			if (callback.id == 10) //MediumSlider
			{
				string value = std::to_string(mediumSlider->getValue());
				double gain = ::strtod(value.c_str(), NULL);
				gain = gain / 100;
				player->MediumEqModification(gain);
			}

			if (callback.id == 11) //TrebbleSlider
			{
				string value = std::to_string(trebbleSlider->getValue());
				double gain = ::strtod(value.c_str(), NULL);
				gain = gain / 100;
				player->TrebbleEqModification(gain);
			}

			if (callback.id == 12) //speedSlider
			{	
				string value = std::to_string(speedSlider->getValue());
				double gain = ::strtod(value.c_str(), NULL);
				gain = gain / 10;
				player->SpeedModification(gain);
			}

			if (callback.id == 13) //PitchSlider
			{
				string value = std::to_string(pitchSlider->getValue());
				double gain = ::strtod(value.c_str(), NULL);
				gain = gain / 10;
				player->PitchModification(gain);
			}
		}

		window.clear();

		// Draw all created widgets
		gui.draw();

		window.display();
	}

	delete player;
	delete fileManage;
	delete uiBuilder;
	return EXIT_SUCCESS;
}