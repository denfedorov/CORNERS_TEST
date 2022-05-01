#include "BaseGameGS.h"

BaseGameGS::BaseGameGS(void) {
	setType(BASEGAME_SCREEN);
	Load();
}

BaseGameGS::~BaseGameGS(void) {
	Unload();
}

void BaseGameGS::deskMouseDown(GameLogicData& gdata, int screenx, int screeny) {

	deskx = screenx / 60;
	desky = screeny / 60;

	switch (gdata.currDesk.field[desky][deskx].type) {
	case AI_CELL:
		break;
	case PLAYER_CELL:
		gdata.currDesk.unselect();
		gdata.currDesk.field[desky][deskx].action = SELECTED;
		break;
	case FREE_CELL:
		if (gdata.currDesk.mayPoint(deskx, desky)) {
			gdata.currDesk.unpoint();
			gdata.currDesk.field[desky][deskx].action = POINTED;
		}
		break;
	}

}

bool BaseGameGS::someoneWin(void) {
	return ai_wins || player_wins;
}

bool BaseGameGS::desckMouseUp(GameLogicData& gdata) {
	if (gdata.findPlayerMoveIndexes()) {
		gdata.PlayerMove();
		return true;
	}
	return false;
}

StateType  BaseGameGS::processEvent(ALLEGRO_EVENT& event, GameLogicData& gdata) {
	if (event.type == ALLEGRO_EVENT_KEY_UP) {
		if (event.keyboard.keycode == ALLEGRO_KEY_U) {
			if (!someoneWin()) {
				if (gdata.undoDesk()) {
					NeedRedraw();
				}
			}
		}
		else
			if (event.keyboard.keycode == ALLEGRO_KEY_R) {
				if (gdata.Restart()) {
					player_wins = false;
					ai_wins = false;
					NeedRedraw();
				}
				return this->getType();
			}
	}

	StateType next_gamestate = BASEGAME_SCREEN;

	if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		if (event.mouse.x > 0
			&& event.mouse.y > 0
			&& event.mouse.x < 480
			&& event.mouse.y < 480
			) {
			if (!player_wins && !ai_wins) {
				deskMouseDown(gdata, event.mouse.x, event.mouse.y);
			}

		}
		NeedRedraw();
	}
	else
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			if (!player_wins && !ai_wins) {
				if (desckMouseUp(gdata)) {
					if (gdata.currDesk.playerWins()) {
						player_wins = true;
						NeedRedraw();
					}
					else {
						next_gamestate = AI_TURN_SCREEEN;
					}
					NeedRedraw();
				}
			}
		}
	return next_gamestate;
};

void BaseGameGS::Load() {
	blackColor = al_map_rgb(0, 0, 0);
	whiteColor = al_map_rgb(255, 255, 255);
	redColor = al_map_rgb(255, 70, 70);
	greenColor = al_map_rgb(60, 255, 60);
	blueColor = al_map_rgb(70, 70, 255);

	desk_b = al_load_bitmap("data/desk.png");

	font_gui = al_load_font("data/MoonLaser.ttf", 18, 0);
};

void BaseGameGS::Unload() {
	al_destroy_bitmap(desk_b);
	al_destroy_font(font_gui);
};

void BaseGameGS::Enter(ALLEGRO_DISPLAY* display, GameLogicData& gdata) {
	Draw(display, gdata);
	ai_wins = gdata.currDesk.aiWins();
	redraw = false;
}
void BaseGameGS::Leave(ALLEGRO_DISPLAY* display, GameLogicData& gdata) {
	this->Draw(display, gdata);
};

void BaseGameGS::DrawCells(GameLogicData& gdata) {
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			float sx = x * 60;
			float sy = y * 60;
			switch (gdata.currDesk.field[y][x].type) {
			case FREE_CELL:
				break;
			case PLAYER_CELL:
				al_draw_filled_circle(sx + 30, sy + 30, 25, greenColor);
				break;
			case AI_CELL:
				al_draw_filled_circle(sx + 30, sy + 30, 25, blueColor);
				break;
			}
			switch (gdata.currDesk.field[y][x].action) {
			case UNSELECTED:
				break;
			case SELECTED:
				al_draw_circle(sx + 30, sy + 30, 25, redColor, 5);
				break;
			case POINTED:
				al_draw_filled_circle(sx + 30, sy + 30, 15, redColor);
				break;
			}

		}
	}
}


void BaseGameGS::Draw(ALLEGRO_DISPLAY* display, GameLogicData& gdata) {
	al_set_target_backbuffer(display);
	al_clear_to_color(blackColor);

	al_draw_textf(font_gui, whiteColor, 480 + 160 / 2, 50, ALLEGRO_ALIGN_CENTRE, "ESC - Exit");


	al_draw_textf(font_gui, whiteColor, 480 + 160 / 2, 100, ALLEGRO_ALIGN_CENTRE, "R - Restart");

	if (!someoneWin()) {
		al_draw_textf(font_gui, whiteColor, 480 + 160 / 2, 150, ALLEGRO_ALIGN_CENTRE, "U - Undo");
	}

	/*if (desky >= 0 && deskx >= 0) {
	al_draw_textf(
		font_gui,
		whiteColor,
		480 + 160 / 2, 200, ALLEGRO_ALIGN_CENTRE,
		"(%d,%d) ai:%d ", desky, deskx,
		gdata.currDesk.getCell(deskx,desky)->Goal
	);
}
*/

	if (player_wins) {
		al_draw_textf(font_gui, greenColor, 480 + 160 / 2, 230, ALLEGRO_ALIGN_CENTRE, "YOU WIN!");
	}
	else
		if (ai_wins) {
			al_draw_textf(font_gui, greenColor, 480 + 160 / 2, 230, ALLEGRO_ALIGN_CENTRE, "YOU FAIL!");
		}


	al_draw_bitmap(desk_b, 0, 0, 0);

	DrawCells(gdata);

	al_flip_display();
};
