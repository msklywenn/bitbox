#include "guiname.h"

#include "font.h"

GUIName::GUIName()
	: GUIElement(144, 3, MAXCHARS * 8, 8), len(4), active(false)
{
	memcpy(name, "tune", len+1);

	fontPrint(surface, name, 0, 0);
}

void GUIName::update()
{
	clear();
	fontPrint(surface, name, 0, 0);
	if ( active ) {
		SDL_EnableUNICODE(1);
		fontPrint(surface, "_", len*8, 0);
	} else {
		SDL_EnableUNICODE(0);
	}
}

bool GUIName::process(SDL_Event * event)
{
	if ( event->type == SDL_MOUSEBUTTONDOWN ) {
		if ( test(event->button.x, event->button.y) )
			active = true;
		else
			active = false;
	} else if ( event->type == SDL_KEYDOWN && active ) {
		if ( event->key.keysym.sym == SDLK_BACKSPACE && len > 0 ) {
			len--;
			name[len] = 0;
		} else if ( len < MAXCHARS-2
				&& ( ( event->key.keysym.unicode >= 'a'
					&& event->key.keysym.unicode <= 'z' )
				|| ( event->key.keysym.unicode >= 'A'
					&& event->key.keysym.unicode <= 'Z' )
				|| event->key.keysym.unicode == '-'
				|| ( event->key.keysym.unicode >= '0'
					&& event->key.keysym.unicode <= '9' ) ) ) {
			name[len] = event->key.keysym.unicode & 0x7F;
			len++;
			name[len] = 0;
		}
	}

	update();

	return true;
}
