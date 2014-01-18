#include "palette.h"
#include <SDL.h>

static SDL_Surface * palette;

void paletteLoad()
{
	palette = SDL_LoadBMP("data/palette.bmp");
}

void paletteDestroy()
{
	SDL_FreeSurface(palette);
}

unsigned int paletteColor(int n)
{
	return ((unsigned int *)palette->pixels)[n]>>8|0xFF000000;
}
