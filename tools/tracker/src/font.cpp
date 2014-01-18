#include "font.h"

static SDL_Surface * font = 0;

void fontLoad()
{
	font = SDL_LoadBMP("data/font.bmp");
}

void fontDestroy()
{
	SDL_FreeSurface(font);
}

void fontPrint(SDL_Surface * surface, char * txt, int x, int y, Uint32 color)
{
	unsigned int * pix = (unsigned int *) surface->pixels + x + y * surface->w;

	while ( *txt != 0 && x + 7 < surface->w ) {
		unsigned char * f = (unsigned char *) font->pixels
				+ 8 * 8 * 3 * ((*txt)-0x20);
		for ( int i = 8 ; i > 0 ; i-- ) {
			for ( int i = 8 ; i > 0 ; i--, f += 3, pix++ )
				if ( *f )
					*pix = color;
			pix += surface->w - 8;
		}
		pix -= surface->w * 8 - 8;
		txt++;
		x += 8;
	}
}
