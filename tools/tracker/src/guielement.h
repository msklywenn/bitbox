#ifndef _GUIELEMENT_H_
#define _GUIELEMENT_H_

#include <SDL.h>
#include "guievents.h"

class GUIElement {
protected:
	SDL_Surface * surface;
	SDL_Rect area;

	void clear();

public:
	GUIElement(int x, int y, int w, int h);
	virtual ~GUIElement();

	SDL_Rect * getArea() { return & area; }
	inline bool test(int x, int y) const {
		return (x >= area.x && y >= area.y && x < area.x + area.w && y < area.y + area.h);
	}

	void render(SDL_Surface * screen);

	virtual bool process(SDL_Event * event);
};

#endif // _GUIELEMENT_H_
