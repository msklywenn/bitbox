#include "guistatusbar.h"
#include "font.h"
#include <stdarg.h>
#include <stdio.h>

GUIStatusBar::GUIStatusBar()
	: GUIElement(8, 480-16, 640-16, 8)
{
	print("Plop Tracker by MsK` [Version 0]");
}

void GUIStatusBar::print(char * msg)
{
	clear();
	fontPrint(surface, msg, 0, 0);
}

void GUIStatusBar::printf(const char * msg, ...)
{
	static char buffer[80];
	va_list list;
	va_start(list, msg);
	vsnprintf(buffer, 80, msg, list);
	print(buffer);
	va_end(list);
}

bool GUIStatusBar::process(SDL_Event * event)
{
	if ( event->type == SDL_USEREVENT && event->user.code == GUI_STATUS )
		return true;
	return false;
}
