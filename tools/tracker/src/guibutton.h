#ifndef _GUIBUTTON_H_
#define _GUIBUTTON_H_

#include "guielement.h"

class Action
{
public:
	virtual void job() = 0;
};

class GUIButton : public GUIElement {
	Action * action;

public:
	GUIButton(int x, int y, int w, int h, Action * a);
	bool process(SDL_Event * event);
};

#endif // _GUIBUTTON_H_
