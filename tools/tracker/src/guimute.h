#ifndef _GUIMUTE_H_
#define _GUIMUTE_H_

#include "guielement.h"
#include "synth.h"

class GUIMute : public GUIElement {
	Synth * synth;

public:
	GUIMute(Synth *);
	bool process(SDL_Event * event);
};

#endif // _GUIMUTE_H_
