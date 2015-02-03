#include "TGUI\TGUI.hpp"
#include "fmod\fmod.hpp"
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include "fmod\fmod_codec.h"
#include "fmod\fmod_common.h"
#include "fmod\fmod_dsp.h"
#include "fmod\fmod_dsp_effects.h"
#include "fmod\fmod_output.h"
#include "fmod\fmod_studio.h"
#include "fmod\fmod_studio.hpp"
#include "fmod\fmod_studio_common.h"


using namespace std;
//using namespace SFMOD;

int main()
{
	//SoundSystem* sound = new SoundSystem();
	FMOD::System     *system;
	FMOD::Sound      *sound1;
	FMOD::Channel    *channel = 0;
	FMOD_RESULT      result;
	unsigned int      version;
	int numDrivers;

	result = FMOD::System_Create(&system);
	result = system->getVersion(&version);
	result = system->getNumDrivers(&numDrivers);
	result = system->init(100, FMOD_INIT_NORMAL, 0);

	result = system->createSound("songs/Dragon_Roost_Island.mp3", FMOD_DEFAULT, 0, &sound1);
	
	//result = system->playSound(sound1, 0, false, &channel);

	// Play the sound, with loop mode
	//sound.playSound(soundSample, true);

	// Do something meanwhile...

	// Release the sound
	//sound.releaseSound(soundSample);
	//handle = new FSOUND_Sample_Load(0, "YourFileName", 0, 0, 0);
	//FSOUND_PlaySound(0, handle);
	//SimpleFMOD fmod;
	//fmod.LoadSong("songs/Dragon_Roost_Island.mp3");
	sf::RenderWindow window(sf::VideoMode(1000, 800), "DjScratcher");
	tgui::Gui gui = tgui::Gui(window);
	gui.setGlobalFont("TGUI/fonts/DejaVuSans.ttf");
	//SFMOD::Song chart();

	tgui::ComboBox::Ptr songList(gui);
	songList->load("TGUI/widgets/Black.conf");
	songList->setPosition(720, 150);
	songList->setSize(200, 30);
	songList->addItem("test");

	tgui::Label::Ptr listeningLabel(gui);
	listeningLabel->load("TGUI/widgets/White.conf");
	listeningLabel->setText("À l'écoute: ");
	listeningLabel->setSize(200, 35);
	listeningLabel->setPosition(100, 35);

	

	tgui::Label::Ptr bassLabel(gui);
	bassLabel->load("TGUI/widgets/White.conf");
	bassLabel->setText("Basse");
	bassLabel->setSize(200, 30);
	bassLabel->setPosition(90, 150);

	tgui::Label::Ptr speedLabel(gui);
	speedLabel->load("TGUI/widgets/White.conf");
	speedLabel->setText("Vitesse");
	speedLabel->setSize(200, 30);
	speedLabel->setPosition(90, 250);

	tgui::Label::Ptr otherLabel(gui);
	otherLabel->load("TGUI/widgets/White.conf");
	otherLabel->setText("Autre");
	otherLabel->setSize(200, 30);
	otherLabel->setPosition(90, 350);

	tgui::Label::Ptr volumeLabel(gui);
	volumeLabel->load("TGUI/widgets/White.conf");
	volumeLabel->setText("Volume");
	volumeLabel->setSize(200, 30);
	volumeLabel->setPosition(760, 530);


	tgui::Button::Ptr updateButton(gui);
	updateButton->load("TGUI/widgets/Black.conf");
	updateButton->setSize(100, 40);
	updateButton->setPosition(820, 110);
	updateButton->setText("Rafraichir la liste");
	updateButton->bindCallback(tgui::Button::LeftMouseClicked);
	updateButton->setCallbackId(4);

	tgui::Slider::Ptr bassSlider(gui);
	bassSlider->load("TGUI/widgets/White.conf");
	bassSlider->setMaximum(20);
	bassSlider->setMinimum(0);
	bassSlider->setValue(10);
	bassSlider->setVerticalScroll(false);
	bassSlider->setSize(300, 15);
	bassSlider->setPosition(100, 200);

	tgui::Slider::Ptr vocalSlider(gui);
	vocalSlider->load("TGUI/widgets/White.conf");
	vocalSlider->setMaximum(20);
	vocalSlider->setMinimum(0);
	vocalSlider->setValue(10);
	vocalSlider->setVerticalScroll(false);
	vocalSlider->setSize(300, 15);
	vocalSlider->setPosition(100, 300);

	tgui::Slider::Ptr otherSlider(gui);
	otherSlider->load("TGUI/widgets/White.conf");
	otherSlider->setMaximum(20);
	otherSlider->setMinimum(0);
	otherSlider->setValue(10);
	otherSlider->setVerticalScroll(false);
	otherSlider->setSize(300, 15);
	otherSlider->setPosition(100, 400);

	tgui::Slider::Ptr volSlider(gui);
	volSlider->load("TGUI/widgets/BabyBlue.conf");
	volSlider->setVerticalScroll(true);
	volSlider->setMaximum(100);
	volSlider->setMinimum(0);
	volSlider->setValue(50);
	volSlider->setSize(15, 300);
	volSlider->setPosition(900, 400);


	tgui::Button::Ptr playButton(gui);
	playButton->load("TGUI/widgets/Black.conf");
	playButton->setSize(100, 60);
	playButton->setPosition(250, 600);
	playButton->setText("Play");
	playButton->bindCallback(tgui::Button::LeftMouseClicked);
	playButton->setCallbackId(1);

	tgui::Button::Ptr backButton(gui);
	backButton->load("TGUI/widgets/White.conf");
	backButton->setSize(100, 60);
	backButton->setPosition(100, 600);
	backButton->setText("Back");
	backButton->bindCallback(tgui::Button::LeftMouseClicked);
	backButton->setCallbackId(2);

	tgui::Button::Ptr newButton(gui);
	newButton->load("TGUI/widgets/White.conf");
	newButton->setSize(100, 60);
	newButton->setPosition(400, 600);
	newButton->setText("Next");
	newButton->bindCallback(tgui::Button::LeftMouseClicked);
	newButton->setCallbackId(3);

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
			if (callback.id == 1 || 2 || 3)
			{
				OPENFILENAME ofn;       // common dialog box structure
				char szFile[260];       // buffer for file name
				HWND hwnd = HWND();              // owner window
				HANDLE hf;              // file handle

				// Initialize OPENFILENAME
				ZeroMemory(&ofn, sizeof(ofn));
				ofn.lStructSize = sizeof(ofn);
				ofn.hwndOwner = hwnd;
				ofn.lpstrFile = szFile;
				// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
				// use the contents of szFile to initialize itself.
				ofn.lpstrFile[0] = '\0';
				ofn.nMaxFile = sizeof(szFile);
				ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
				ofn.nFilterIndex = 1;
				ofn.lpstrFileTitle = NULL;
				ofn.nMaxFileTitle = 0;
				ofn.lpstrInitialDir = NULL;
				ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

				// Display the Open dialog box. 

				if (GetOpenFileName(&ofn) == TRUE)
				{
					hf = CreateFile(ofn.lpstrFile,
						GENERIC_READ,
						0,
						(LPSECURITY_ATTRIBUTES)NULL,
						OPEN_EXISTING,
						FILE_ATTRIBUTE_NORMAL,
						(HANDLE)NULL);
					
				}
			}
		}

		window.clear();

		// Draw all created widgets
		gui.draw();

		window.display();
	}

	return EXIT_SUCCESS;
}