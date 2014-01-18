#include "guiwaveout.h"
#include "guievents.h"
#include <stdio.h>

GUIWaveOut::GUIWaveOut(Synth * s, GUIName * n, GUIStatusBar * sb)
	: GUIElement(569, 16, 55, 11), synth(s), name(n), status(sb)
{
}

bool GUIWaveOut::process(SDL_Event * event)
{
	if ( event->type == SDL_MOUSEBUTTONDOWN 
			&& test(event->button.x, event->button.y) ) {
		static char filename[256];
		sprintf(filename, "%s.wav", name->get());
		if ( synth->waveOut(filename) )
			status->printf("Waveout : %s written.", filename);
		else
			status->printf("Waveout : failed to write %s.", filename);
		PushUserEvent(GUI_STATUS);
	}

	return false;
}
