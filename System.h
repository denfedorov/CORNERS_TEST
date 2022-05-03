#pragma once
#include "engineheaders.h"

class System
{
public:

	ALLEGRO_MIXER* mixer;
	ALLEGRO_VOICE* mainchannel;
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;

	System(void){
		display = NULL;
		queue = NULL;
		mixer = NULL;
	}

};

