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
	StateType  processEvent(ALLEGRO_EVENT& event, GameLogicData& gdata);

	void Load(void);
	
	void Unload(void);

	void AiTurn(GameLogicData& gdata);
	void Enter(ALLEGRO_DISPLAY* display, GameLogicData& gdata);
	void Leave(ALLEGRO_DISPLAY* display, GameLogicData& gdata);
	void Draw(ALLEGRO_DISPLAY* display, GameLogicData& gdata);

};
