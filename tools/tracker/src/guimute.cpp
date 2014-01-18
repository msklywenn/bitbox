#include "guimute.h"
#include "font.h"
#include "palette.h"

GUIMute::GUIMute(Synth * synth)
	: GUIElement(44, 34, 448, 9), synth(synth)
{
}

bool GUIMute::process(SDL_Event * event)
{
	if ( event->type == SDL_MOUSEBUTTONDOWN ) {
		if ( test(event->button.x, event->button.y) ) {
			int ch = (event->button.x - 44)/56;
			bool mute = synth->toggleMute(ch);
			unsigned int * pix = (unsigned int *) surface->pixels
				+ ch * 56 + 3 + 448 * 4;
			const unsigned int len = 4*8*6;
			if ( mute ) {
				memset(pix, 0xFF, len); // white line
			} else {
				memset(pix, 0x00, len); // clear line
			}
			return true;
		}
	}

	return false;
}
