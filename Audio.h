#pragma once
#include "miniaudio.h"

class Audio
{
public:
	void Init();
	void Shutdown();

	void Play(ma_sound& sound);
	void Stop(ma_sound& sound);
	//void PlayEffect(const char* name);

	ma_sound musicLvl1;
	ma_sound musicLvl2;
	ma_sound musicMenu;
	ma_sound musicGameOver;


	ma_sound explosionSound;
	ma_sound placeBombSound;
	ma_sound playerDeathSound;
	ma_sound walkHorSound;
	ma_sound walkVerSound;
	ma_sound gameOverSound;
private:
	ma_engine engine;

};

