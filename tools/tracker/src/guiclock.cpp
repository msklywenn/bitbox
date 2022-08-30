#include "guiclock.h"

#include "font.h"
#include "palette.h"

GUIClock::GUIClock(Tune * tune)
	: GUIElement(64, 3, 40, 8), tune(tune)
{
	fontPrint(surface, "00:00", 0, 0, paletteColor(6));
}

bool GUIClock::process(SDL_Event * event)
{
	if ( event->type == SDL_USEREVENT && event->user.code == GUI_CURRENTROW ) {
		int row = *(int*)&event->user.data1;
		char str[6];
		int minutes = row / tune->rpm;
		int seconds = (row % tune->rpm) * 60 / tune->rpm;
		sprintf(str, "%02d:%02d", minutes, seconds);
		clear();
		fontPrint(surface, str, 0, 0, paletteColor(6));

		return true;
	}

	return false;
}
