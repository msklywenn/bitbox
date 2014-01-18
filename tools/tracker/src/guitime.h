#ifndef _GUITIME_H_
#define _GUITIME_H_

#include "guielement.h"
#include "synth.h"

class GUITime : public GUIElement {
	static const int DELAY = 300;

	int offset;
	int row;
	int lastClick;
	int lastY;

	Synth * synth;

	void update();

public:
	GUITime(Synth *);
	bool process(SDL_Event * event);
};

#endif // _GUITIME_H_
