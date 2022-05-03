#pragma once

// Состояние игрового процесса в стартовом окне

#include "GameState.h"
#include "GameLogicData.h"

class MainScreenGS : public GameState {
	ALLEGRO_FONT* font_gui;
	ALLEGRO_BITMAP* joystick_b;
	ALLEGRO_COLOR blackColor;
	ALLEGRO_COLOR whiteColor;


public:

	MainScreenGS(void);
	~MainScreenGS(void);
	StateType  processEvent(ALLEGRO_EVENT& event, GameLogicData& gdata);
	void Load();
	void Unload();

	void Enter(System& sys, GameLogicData& gdata);
	void Leave(System& sys, GameLogicData& gdata);

	void Draw(System& sys, GameLogicData& gdata);


};