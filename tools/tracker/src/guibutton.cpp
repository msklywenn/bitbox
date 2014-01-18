#include "guibutton.h"

GUIButton::GUIButton(int x, int y, int w, int h, Action * a)
	: GUIElement(x, y, w, h), action(a)
{
}

bool GUIButton::process(SDL_Event * event)
{
	if ( event->type == SDL_MOUSEBUTTONDOWN
			&& test(event->button.x, event->button.y) ) {
		action->job();
	}

	return false;
}
