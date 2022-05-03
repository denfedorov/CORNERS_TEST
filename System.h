#pragma once
#include "engineheaders.h"

class System
{
public:

	ALLEGRO_AUDIO_STREAM* stream;
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;

	System(void){
		display = NULL;
		queue = NULL;
		stream = NULL;
	}

};

