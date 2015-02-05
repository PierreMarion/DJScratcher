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
}
Player::~Player()
{
	delete[] spec;	

	FMODsys->release();
	currentSound->release();
}
void Player::Load()
{
	FMODErrorCheck(FMODsys->createStream("WoW_Medley.mp3", FMOD_SOFTWARE, 0, &currentSound));
}
void Player::Play()
{
	FMODErrorCheck(FMODsys->playSound(FMOD_CHANNEL_FREE, this->currentSound, true, &this->channel));
	
	FMODErrorCheck(this->channel->setChannelGroup(masterSound));

	this->channel->setPaused(false);
	this->channel->setVolume(0.5f);
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

void Player::ChangeVolume(string nVolume)
{

	//HRESULT hr = NULL;
	//bool decibels = false;
	//bool scalar = false;
	//double newVolume = nVolume;

	//CoInitialize(NULL);
	//IMMDeviceEnumerator *deviceEnumerator = NULL;
	//hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER,
	//	__uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
	//IMMDevice *defaultDevice = NULL;

	//hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
	//deviceEnumerator->Release();
	//deviceEnumerator = NULL;

	//IAudioEndpointVolume *endpointVolume = NULL;
	//hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume),
	//	CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
	//defaultDevice->Release();
	//defaultDevice = NULL;

	//// -------------------------
	//float currentVolume = 0;
	//endpointVolume->GetMasterVolumeLevel(&currentVolume);
	////printf("Current volume in dB is: %f\n", currentVolume);

	//hr = endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);
	////CString strCur=L"";
	////strCur.Format(L"%f",currentVolume);
	////AfxMessageBox(strCur);

	//// printf("Current volume as a scalar is: %f\n", currentVolume);
	//if (bScalar == false)
	//{
	//	hr = endpointVolume->SetMasterVolumeLevel((float)newVolume, NULL);
	//}
	//else if (bScalar == true)
	//{
	//	hr = endpointVolume->SetMasterVolumeLevelScalar((float)newVolume, NULL);
	//}
	//endpointVolume->Release();

	//CoUninitialize();

	//return FALSE;
	float value = ::atof(nVolume.c_str());
	this->channel->setVolume(value);
}