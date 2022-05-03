#pragma once

#include "common.h"
#include "engineheaders.h"
#include "System.h"

#include "GameLogicData.h"
#include "GameState.h"
#include "MainScreenGS.h"
#include "BaseGameGS.h"
#include "AITurnGS.h"

//Основной класс

typedef map<StateType, GameState*> GameStateMap;

class Game {
private:

	System sys;

	ALLEGRO_BITMAP* icon1;
	
	ALLEGRO_SAMPLE* greets_sound;
	ALLEGRO_SAMPLE_INSTANCE* greetssound_inst;
	
	ALLEGRO_TIMER* timer;
	
	bool first_time;

	MainScreenGS *main_screenGS;
	BaseGameGS *base_gameGS;
	AITurnGS *ai_turnGS;

	GameStateMap states;
	StateType currState;
	

	bool fullscreen;

	void procesState(ALLEGRO_EVENT& event);


	void gameLogicInit(void);

	void gameLogicShutdown(void);

	void systemInit(void);
	void sytemShutdown(void);
	
	bool systemContinue(void);

	bool getScreenMode() {
		return fullscreen;
	}
	void displayInit(bool fullscreen);

public:
	
	GameLogicData gamedata;

	 Game(void) {
		first_time = true;
		systemInit();
		gameLogicInit();
		first_time = false;
	}

	~Game(void) {
		gameLogicShutdown();
		sytemShutdown();
	}

	void systemGo(void) {
		al_play_sample_instance(greetssound_inst);
		while (!systemContinue()) {};
	}
};

