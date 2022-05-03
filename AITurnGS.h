#pragma once

// ��������� �������� �������� ��� ���� ��

#include "GameState.h"
#include "GameLogicData.h"
#include "AiThinker.h"

class AITurnGS : public GameState {
	ALLEGRO_BITMAP* wait_b;
	ALLEGRO_COLOR blackColor;

public:
	AITurnGS(System &sys);
	~AITurnGS(void);
	StateType  processEvent(ALLEGRO_EVENT &event, GameLogicData& gdata);

	void Load(System &sys);
	
	void Unload(void);

	void AiTurn(GameLogicData& gdata);
	void Enter(System& sys, GameLogicData& gdata);
	void Leave(System& sys, GameLogicData& gdata);
	void Draw(System& sysy, GameLogicData& gdata);

};
