#ifndef _GUISPECTRUM_H_
#define _GUISPECTRUM_H_

#include "guielement.h"
#include "synth.h"

class GUISpectrum : public GUIElement {
	Synth * synth;

	static const int Columns = 16;
	int peaks[Columns];
	int peakTime[Columns];

	void drawColumn(int col, int height);
	void drawPeaks();

public:
	GUISpectrum(Synth * s);
	~GUISpectrum();
	bool process(SDL_Event *);
};

#endif // _GUISPECTRUM_H_
