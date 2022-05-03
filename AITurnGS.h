#pragma once

// Состояние игрового процесса про ходе ИИ

#include "GameState.h"
#include "GameLogicData.h"
#include "AiThinker.h"

class AITurnGS : public GameState {
	ALLEGRO_BITMAP* wait_b;
	ALLEGRO_COLOR blackColor;

public:
	AITurnGS(void);
	~AITurnGS(void);
	StateType  processEvent(ALLEGRO_EVENT &event, GameLogicData& gdata);

	void Load(void);
	
	void Unload(void);

	void AiTurn(GameLogicData& gdata);
	void Enter(System& sys, GameLogicData& gdata);
	void Leave(System& sys, GameLogicData& gdata);
	void Draw(System& sysy, GameLogicData& gdata);

};
