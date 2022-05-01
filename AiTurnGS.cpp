#include "GameLogicData.h"
#include "AITurnGS.h"

AITurnGS::AITurnGS(void) {
	setType(AI_TURN_SCREEEN);
	Load();
}

AITurnGS::~AITurnGS(void) {
	Unload();
}

StateType  AITurnGS::processEvent(ALLEGRO_EVENT& event, GameLogicData& gdata) {
	return BASEGAME_SCREEN;
};

void AITurnGS::Load(void) {
	blackColor = al_map_rgb(0, 0, 0);
	wait_b = al_load_bitmap("data/wait.png");
};

void AITurnGS::Unload(void) {
	al_destroy_bitmap(wait_b);
};

void AITurnGS::AiTurn(GameLogicData& gdata) {
	AiThinker thinker(&gdata.currDesk);

	thinker.Think();

	gdata.currDesk = thinker.desigion_desk;
	gdata.saveDesk();
}

void AITurnGS::Enter(ALLEGRO_DISPLAY* display, GameLogicData& gdata) {
	Draw(display, gdata);

	AiTurn(gdata);

	al_draw_filled_rectangle(480 + 10, 480 - 200, 480 + 10 + 140, 480 - 200 + 140, blackColor);
	al_flip_display();
}

void AITurnGS::Leave(ALLEGRO_DISPLAY* display, GameLogicData& gdata) {

};

void AITurnGS::Draw(ALLEGRO_DISPLAY* display, GameLogicData& gdata) {

	al_draw_bitmap(wait_b, 480 + 10, 480 - 200, 0);
	al_flip_display();
};