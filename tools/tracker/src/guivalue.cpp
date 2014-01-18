#include "guivalue.h"
#include "font.h"

void GUIValue::update()
{
	if ( *value < min )
		*value = min;
	if ( *value > max )
		*value = max;

	clear();

	static char str[7];
	sprintf(str, "<%4d>", *value);
	fontPrint(surface, str, 0, 0);
}

bool GUIValue::process(SDL_Event * event)
{
	bool up = false;

	if ( event->type == SDL_MOUSEBUTTONDOWN && event->button.button == 1 ) {
		if ( test(event->button.x, event->button.y) ) {
			mousedown = true;
			int x = event->button.x - area.x;
			if ( x < 8 ) {
				(*value)--;
				up = true;
			} else if ( x > 5*8 ) {
				(*value)++;
				up = true;
			} else {
				dx = 0;
				SDL_WM_GrabInput(SDL_GRAB_ON);
				SDL_ShowCursor(0);
			}
		}
	} else if ( event->type == SDL_MOUSEBUTTONUP ) {
		mousedown = false;
		SDL_WM_GrabInput(SDL_GRAB_OFF);
		SDL_ShowCursor(1);
	} else if ( event->type == SDL_MOUSEMOTION && mousedown ) {
		dx += event->motion.xrel;
		if ( dx < -THRESHOLD ) {
			while ( dx < -THRESHOLD ) {
				(*value)--;
				dx += THRESHOLD;
			}
			up = true;
		} else if ( dx > THRESHOLD ) {
			while ( dx > THRESHOLD ) {
				(*value)++;
				dx -= THRESHOLD;
			}
			up = true;
		}
	}

	if ( up )
		update();
	
	return up;
}
