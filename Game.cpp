#include "Game.h"

void Game::gameLogicInit(void) {

	main_screenGS = new MainScreenGS();
	base_gameGS = new BaseGameGS();
	ai_turnGS = new AITurnGS();

	currState = StateType::MAIN_SCREEN;

	states.emplace(MAIN_SCREEN, (GameState*)main_screenGS);
	states.emplace(BASEGAME_SCREEN, (GameState*)base_gameGS);
	states.emplace(AI_TURN_SCREEEN, (GameState*)ai_turnGS);

	states[currState]->Enter(sys, gamedata);
}

void Game::gameLogicShutdown(void) {
	delete main_screenGS;
	delete base_gameGS;
	delete ai_turnGS;
}

void Game::displayInit(bool _fullscreen) {

	al_stop_timer(timer);

	if (!first_time) {

		al_unregister_event_source(sys.queue, al_get_display_event_source(sys.display));
		al_unregister_event_source(sys.queue, al_get_timer_event_source(timer));
		al_unregister_event_source(sys.queue, al_get_keyboard_event_source());
		al_unregister_event_source(sys.queue, al_get_mouse_event_source());
		al_destroy_event_queue(sys.queue);
		al_destroy_display(sys.display);
	}

	if (_fullscreen) {
		al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	}
	else {
		al_set_new_display_flags(ALLEGRO_WINDOWED);
	}

	sys.display = al_create_display(640, 480);

	if (!sys.display) {
		abort_example("Cannot init display\n");
	}

	sys.queue = al_create_event_queue();

	al_register_event_source(sys.queue, al_get_display_event_source(sys.display));
	al_register_event_source(sys.queue, al_get_keyboard_event_source());
	al_register_event_source(sys.queue, al_get_mouse_event_source());
	al_register_event_source(sys.queue, al_get_timer_event_source(timer));

	fullscreen = _fullscreen;

	if (!fullscreen) {
		al_set_display_icon(sys.display, icon1);
		al_set_window_title(sys.display, "Corners");
	}

	al_start_timer(timer);

}

void Game::procesState(ALLEGRO_EVENT& event) {
	StateType prevState = currState;

	currState = states[prevState]->processEvent(event, this->gamedata);

	if (prevState != currState) {
		states[prevState]->Leave(sys, this->gamedata);
		states[currState]->Enter(sys, this->gamedata);
	}

}


bool Game::systemContinue() {

	ALLEGRO_EVENT event;
	al_wait_for_event(sys.queue, &event);

	procesState(event);

	if (event.type == ALLEGRO_EVENT_KEY_UP) {
		if (
			event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
			return true;
		}
		if (
			event.keyboard.keycode == ALLEGRO_KEY_F1) {
			this->displayInit(!this->getScreenMode());
			states[currState]->NeedRedraw();
			return false;
		}
		if (
			event.keyboard.keycode == ALLEGRO_KEY_SPACE && currState == MAIN_SCREEN) {
			states[currState]->Leave(sys, gamedata);
			currState = BASEGAME_SCREEN;
			states[currState]->Enter(sys, gamedata);
			return false;
		}
	}
	if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		return true;
	}
	if (event.type == ALLEGRO_EVENT_TIMER && states[currState]->redraw) {
		states[currState]->Draw(sys, gamedata);
		states[currState]->redraw = false;
	}
	return false;
}

void Game::sytemShutdown() {

	al_destroy_bitmap(icon1);
	al_destroy_timer(timer);
	al_uninstall_system();
}

void Game::systemInit() {

	fullscreen = false;


	if (!al_init()) {
		abort_example("Could not init Allegro.\n");
	}
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_install_mouse();
	al_install_keyboard();
	init_platform_specific();

	if (!al_install_audio()) {
		abort_example("Could not init sound.\n");
	}

	//Init resources

	icon1 = al_load_bitmap("data/icon.tga");
	if (!icon1) {
		abort_example("icon.tga not found\n");
	}


	timer = al_create_timer(1.0 / 10.0);

	displayInit(false);

	/* First icon: Read from file. */
}