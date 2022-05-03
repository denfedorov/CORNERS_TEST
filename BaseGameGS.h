#pragma once

// ��������� �������� �������� � ������� ������

#include "GameState.h"
#include "GameLogicData.h"
#include "GameLogicBase.h"


class BaseGameGS : public GameState {
private:
	ALLEGRO_FONT* font_gui;
	ALLEGRO_BITMAP* desk_b;

	ALLEGRO_COLOR blackColor;
	ALLEGRO_COLOR whiteColor;
	ALLEGRO_COLOR redColor;
	ALLEGRO_COLOR greenColor;
	ALLEGRO_COLOR blueColor;


	int deskx=-1;
	int desky=-1;

	bool player_wins=false;
	bool ai_wins = false;

public:
	BaseGameGS(void);
	~BaseGameGS(void);

	void deskMouseDown(GameLogicData& gdata, int screenx, int screeny);
	bool someoneWin(void);

	bool desckMouseUp(GameLogicData& gdata);

	StateType  processEvent(ALLEGRO_EVENT& event, GameLogicData& gdata);
	
	void Load();
	
	void Unload();

	void Enter(System& sys, GameLogicData& gdata);
	void Leave(System& sys, GameLogicData& gdata);

	void DrawCells(GameLogicData& gdata);

	void Draw(System& sys, GameLogicData& gdata);



};