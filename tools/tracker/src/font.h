#ifndef _FONT_H_
#define _FONT_H_

#include <SDL.h>

void fontLoad();
void fontDestroy();
void fontPrint(SDL_Surface * surface, char * txt, int x, int y,
	  	Uint32 color = 0xFFFFFFFF);
static inline void fontPrint(SDL_Surface * surface, const char * txt,
	   	int x, int y, Uint32 color = 0xFFFFFFFF) {
   fontPrint(surface, (char *) txt, x, y, color);
}

#endif // _FONT_H_
