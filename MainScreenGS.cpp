#include "MainScreenGS.h"
#include "GameState.h"
#include "GameLogicData.h"

MainScreenGS::MainScreenGS(System &sys) {
	setType(MAIN_SCREEN);
	Load(sys);
}
MainScreenGS::~MainScreenGS(void) {
	Unload();
}

StateType  MainScreenGS::processEvent(ALLEGRO_EVENT& event, GameLogicData& gdata) {
	return this->getType();
};

void MainScreenGS::Load(System &sys) {
	font_gui = al_load_font("data/MoonLaser.ttf", 24, 0);
	joystick_b = al_load_bitmap("data/joy.png");
	blackColor = al_map_rgb(0, 0, 0);
	whiteColor = al_map_rgb(255, 255, 255);
};
void MainScreenGS::Unload(void) {
	al_destroy_bitmap(joystick_b);
	al_destroy_font(font_gui);
};

void MainScreenGS::Enter(System &sys, GameLogicData& gdata) {
	NeedRedraw();
}
void MainScreenGS::Leave(System& sys, GameLogicData& gdata) {

};

void MainScreenGS::Draw(System& sys, GameLogicData& gdata) {


	al_set_target_backbuffer(sys.display);
	al_clear_to_color(blackColor);

	al_draw_bitmap(joystick_b, 10, 10, 0);

	al_draw_textf(font_gui, whiteColor, 640 / 2, 480 / 4, ALLEGRO_ALIGN_CENTRE, "CORNERS");

	al_draw_textf(font_gui, whiteColor, 640 / 2, 480 / 4 + 100, ALLEGRO_ALIGN_CENTRE, "'SPACE' to Start");

	al_draw_textf(font_gui, whiteColor, 640 / 2, 480 / 4 + 150, ALLEGRO_ALIGN_CENTRE, "'F1' toggle FULLSCREEN");

	al_draw_textf(font_gui, whiteColor, 640 / 2, 480 / 4 + 200, ALLEGRO_ALIGN_CENTRE, "'ESC' to QUIT");

	al_flip_display();
};