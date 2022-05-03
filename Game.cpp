#include "Game.h"

void Game::gameLogicInit(void) {

	main_screenGS = new MainScreenGS(sys);
	base_gameGS = new BaseGameGS(sys);
	ai_turnGS = new AITurnGS(sys);

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

	al_destroy_sample_instance(greetssound_inst);
	al_destroy_sample(greets_sound);

	al_destroy_mixer(sys.mixer);
	al_destroy_voice(sys.mainchannel);

	al_uninstall_system();
}

void Game::systemInit() {

	fullscreen = false;


	if (!al_init()) {
		abort_example("Could not init Allegro.\n");
	}
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_acodec_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_install_mouse();
	al_install_keyboard();
	if (!al_install_audio()) {
		abort_example("Could not init sound!\n");
	}

	init_platform_specific();

	sys.mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32,
		ALLEGRO_CHANNEL_CONF_2);
	if (!sys.mixer) {
		abort_example("al_create_mixer failed.\n");
	}

	sys.mainchannel = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16,
		ALLEGRO_CHANNEL_CONF_2);
	if (!sys.mainchannel) {
		abort_example("Could not create ALLEGRO_VOICE from sample\n");
	}

	if (!al_attach_mixer_to_voice(sys.mixer, sys.mainchannel)) {
		abort_example("al_attach_mixer_to_voice failed.\n");
	}

	//Init resources

	icon1 = al_load_bitmap("data/icon.tga");
	if (!icon1) {
		abort_example("icon.tga not found\n");
	}

	greets_sound = al_load_sample("data/greets.wav");
	if (!greets_sound) {
		abort_example("Could not load sample from '%s'!\n",
			"turn.mp3");
	}
	else {
		greetssound_inst = al_create_sample_instance(greets_sound);
		al_attach_sample_instance_to_mixer(greetssound_inst, sys.mixer);
	}
	

	timer = al_create_timer(1.0 / 10.0);

	displayInit(false);

	/* First icon: Read from file. */
}