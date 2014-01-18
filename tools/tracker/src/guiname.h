#ifndef _GUINAME_H_
#define _GUINAME_H_

#include "guielement.h"

class GUIName : public GUIElement {
	static const int MAXCHARS = 60;
	int len;
	bool active;
	char name[MAXCHARS];

	void update();

public:
	GUIName();
	bool process(SDL_Event * event);
	const char * get() const { return name; }
};

#endif // _GUINAME_H_
