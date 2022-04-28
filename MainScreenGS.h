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

	MainScreenGS(void) {
		setType(MAIN_SCREEN);
		Load();
	}
	~MainScreenGS(void) {
		Unload();
	}

	StateType  processEvent(ALLEGRO_EVENT& event, GameLogicData& gdata) {
		return this->getType(); 
	};
	
	void Load() {
		font_gui = al_load_font("data/MoonLaser.ttf", 24, 0);
		joystick_b = al_load_bitmap("data/joy.png");
		blackColor= al_map_rgb(0, 0, 0);
		whiteColor = al_map_rgb(255, 255, 255);
	};
	void Unload() {
		al_destroy_bitmap(joystick_b);
		al_destroy_font(font_gui);
	};

	void Enter(ALLEGRO_DISPLAY* display, GameLogicData& gdata) {
		NeedRedraw();
	}
	void Leave(ALLEGRO_DISPLAY* display, GameLogicData& gdata) {
	
	};

	void Draw(ALLEGRO_DISPLAY *display, GameLogicData &gdata) {


		al_set_target_backbuffer(display);
		al_clear_to_color(blackColor);

		al_draw_bitmap(joystick_b, 10, 10, 0);

		al_draw_textf(font_gui, whiteColor, 640 / 2, 480 / 4, ALLEGRO_ALIGN_CENTRE, "CORNERS");

		al_draw_textf(font_gui, whiteColor, 640 / 2, 480 / 4 + 100, ALLEGRO_ALIGN_CENTRE, "'SPACE' to Start");

		al_draw_textf(font_gui, whiteColor, 640 / 2, 480 / 4 + 150, ALLEGRO_ALIGN_CENTRE, "'F1' toggle FULLSCREEN");

		al_draw_textf(font_gui, whiteColor, 640 / 2, 480 / 4 + 200, ALLEGRO_ALIGN_CENTRE, "'ESC' to QUIT");

		al_flip_display();
	};


};