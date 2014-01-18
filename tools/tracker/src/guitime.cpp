#include "guitime.h"
#include "font.h"
#include "palette.h"
#include "channel.h"
#include <limits.h>

GUITime::GUITime(Synth * synth)
	: GUIElement(9, 69, 32, 384), offset(0), row(0),
	lastClick(INT_MAX), lastY(-1), synth(synth)
{
	update();
}

void GUITime::update()
{
	static char str[5];

	clear();

	for ( int i = 0 ; i < 48 ; i++ ) {
		sprintf(str, "%3X", i + offset);
		fontPrint(surface, str, 0, i*8, paletteColor(6));
	}

	if ( row >= offset && row < offset + 48 ) {
		fontPrint(surface, ">", 24, (row - offset)*8, paletteColor(7));
	}
}

bool GUITime::process(SDL_Event * event)
{
	bool up = false;

	if ( event->type == SDL_MOUSEBUTTONDOWN ) {
		if ( event->button.button == 5 ) { // wheel down
			offset++;
			up = true;
		} else if ( event->button.button == 4 ) { // wheel up
			offset--;
			up = true;
		} else if ( event->button.button == 1 ) { // set current row
			if ( test(event->button.x, event->button.y) ) {
				int y = (event->button.y - area.y)/8;
				if ( SDL_GetTicks() - lastClick < (Uint32) DELAY
						&& y == lastY ) {
					row = y + offset;
					synth->setRow(row);
					up = true;
				} else {
					lastY = y;
					lastClick = SDL_GetTicks();
				}
			}
		}
	} else if ( event->type == SDL_KEYDOWN ) {
		if ( event->key.keysym.sym == SDLK_PAGEDOWN )
			offset += 48;
		else if ( event->key.keysym.sym == SDLK_PAGEUP )
			offset -= 48;
		up = true;
	} else if ( event->type == SDL_USEREVENT ) {
		if ( event->user.code == GUI_SETOFFSET ) {
			offset = (int) event->user.data1;
			up = true;
		} else if ( event->user.code == GUI_CURRENTROW ) {
			row = (int) event->user.data1;
			if ( row > offset+48 ) {
				if ( row > offset+48*2 ) {
					PushUserEvent(GUI_SETOFFSET, (void *) row);
				} else {
					// KEYDOWN is faster than USEREVENT... duh ?
					static SDL_Event event;
					event.type = SDL_KEYDOWN;
					event.key.keysym.sym = SDLK_PAGEDOWN;
					SDL_PushEvent(& event);
				}
			}
			up = true;
		}
	}

	if ( up ) {
		if ( offset < 0 )
			offset = 0;
		if ( offset >= MAXROWS - 48 )
			offset = MAXROWS - 48;
		update();
	}

	return up;
}
