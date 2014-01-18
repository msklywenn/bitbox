#include "guievents.h"

#include <SDL.h>

void PushUserEvent(int code, void * data1, void * data2)
{
	static SDL_Event event;
	event.type = SDL_USEREVENT;
	event.user.code = code;
	event.user.data1 = data1;
	event.user.data2 = data2;
	SDL_PushEvent(& event);
}
