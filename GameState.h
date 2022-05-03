#pragma once
//Общий класс описания состояния игры

#include "common.h"
#include "System.h"
#include "engineheaders.h"
#include "GameLogicData.h"

typedef enum { NULLSCREEEN, MAIN_SCREEN, BASEGAME_SCREEN, AI_TURN_SCREEEN } StateType;

class GameState {
public:
	

	bool redraw = false;

	StateType state_type;

	virtual void Load() {};
	virtual void Unload() {};

	virtual StateType  processEvent(ALLEGRO_EVENT &event, GameLogicData &gdata) { return this->getType(); };

	virtual void Enter(System  &sys, GameLogicData& gdata) {
		NeedRedraw();
	};
	virtual void Leave(System &sys, GameLogicData& gdata) {};

	virtual void Draw(System &sys, GameLogicData& gdata) {};
	
	void NeedRedraw() {
		redraw = true;
	}

	StateType getType(void) {
		return state_type;
	}

	void setType(StateType st) {
		state_type = st;
	}

	bool stateIsSameAs(StateType st) {
		return state_type == st;
	}

	//resurces and other


};