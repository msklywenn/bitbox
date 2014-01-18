#ifndef _GUI_H_
#define _GUI_H_

#include <SDL.h>
#include <list>

#include "guielement.h"

class GUI {
	SDL_Surface * screen;
	SDL_Surface * bg;
	std::list<GUIElement *> elements;

public:
	GUI();
	~GUI();

	void attach(GUIElement * element);

	void render(GUIElement * element);

	void render();
	void fullscreen();

	void process(SDL_Event * event);
};

#endif // _GUI_H_
