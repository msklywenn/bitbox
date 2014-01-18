#include "guioscilloscope.h"

#include "palette.h"

GUIOscilloscope::GUIOscilloscope(Synth * s)
	: GUIElement(502, 263, 128, 64), synth(s)
{
	unsigned int * pixels = (unsigned int *) surface->pixels;

	for ( int i = 0 ; i < 128 ; i++ )
		pixels[i + 32 * 128] = paletteColor(5);
}

static void line(unsigned int * pixels, int x, int y1, int y2)
{
	unsigned int c = paletteColor(4);
	if ( y2 < y1 ) {
		int tmp = y2;
		y2 = y1;
		y1 = tmp;
	}
	for ( int i = y1 ; i <= y2 ; i++ )
		pixels[x + i * 128] = c;
}

bool GUIOscilloscope::process(SDL_Event * event)
{
	int lasty = 32;
	signed short * buffer;
	unsigned int * pixels = (unsigned int *) surface->pixels;

	if ( event->type == SDL_USEREVENT ) {
		if ( event->user.code == GUI_OSCILLOSCOPE ) {
			buffer = synth->getAnalyseBuffer();

			clear();

			// Draw
			for ( int x = 0 ; x < 128 ; x++ ) {
				int y = 32 + buffer[x * Synth::analyseBufferSize / 128]
					/ 0x400;
				if ( y < 0 )
					y = 0;
				else if ( y >= 64 )
					y = 63;
				line(pixels, x, lasty, y);
				lasty = y;
			}

			return true;
		}
	}

	return false;
}
