#ifndef _GUIVU_H_
#define _GUIVU_H_

#include "guielement.h"
#include "synth.h"

class GUIVU : public GUIElement {
	Synth * synth;

	static const int Columns = 10;
	int peaks[Columns];
	int peakTime[Columns];

	void drawColumn(int col, int height);
	void drawPeaks();

public:
	GUIVU(Synth * s);
	bool process(SDL_Event *);
};

#endif // _GUIVU_H_
