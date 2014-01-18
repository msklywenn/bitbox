#include "guielement.h"

GUIElement::GUIElement(int x, int y, int w, int h)
{
	surface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32,
			0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	area.x = x;
	area.y = y;
	area.w = w;
	area.h = h;
}

GUIElement::~GUIElement()
{
	SDL_FreeSurface(surface);
}

void GUIElement::render(SDL_Surface * screen)
{
	SDL_BlitSurface(surface, 0, screen, & area);
}

bool GUIElement::process(SDL_Event * event)
{
	return false;
}

void GUIElement::clear()
{
	unsigned int * pix = (unsigned int *) surface->pixels;
	for ( int i = area.w * area.h ; i > 0 ; i-- )
		*pix++ = 0x00000000;
}
