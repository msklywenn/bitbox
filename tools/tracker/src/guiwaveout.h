#ifndef _GUIWAVEOUT_H_
#define _GUIWAVEOUT_H_

#include "guielement.h"
#include "guiname.h"
#include "guistatusbar.h"
#include "synth.h"

class GUIWaveOut : public GUIElement {
	Synth * synth;
	GUIName * name;
	GUIStatusBar * status;

public:
	GUIWaveOut(Synth * s, GUIName * n, GUIStatusBar * sb);
	bool process(SDL_Event *);
};

#endif // _GUIWAVEOUT_H_
