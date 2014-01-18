#ifndef _GUIOSCILLOSCOPE_H_
#define _GUIOSCILLOSCOPE_H_

#include "guielement.h"
#include "synth.h"

class GUIOscilloscope : public GUIElement {
	Synth * synth;

public:
	GUIOscilloscope(Synth * s);
	bool process(SDL_Event *);
};

#endif // _GUIOSCILLOSCOPE_H_
