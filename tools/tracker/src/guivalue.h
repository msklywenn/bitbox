#ifndef _GUIVALUE_H_
#define _GUIVALUE_H_

#include "guielement.h"

class GUIValue : public GUIElement {
	int min, max;
	int * value;
	bool mousedown;
	int dx;
	static const int THRESHOLD = 10;

public:
	GUIValue(int x, int y, int * value, int min, int max)
		: GUIElement(x, y, 6*8, 8),
		min(min), max(max), value(value), mousedown(false) {
		update();
	}

	void update();

	bool process(SDL_Event * event);
};

#endif // _GUIVALUE_H_
