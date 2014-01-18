#include "guispectrum.h"

#include <math.h>

#include "palette.h"

GUISpectrum::GUISpectrum(Synth * s)
	: GUIElement(502, 186, 128, 64), synth(s)
{
	for ( int i = 0 ; i < Columns ; i++ ) {
		peaks[i] = (Columns-1-i)*4+2;
		peakTime[i] = 0;
		drawColumn(i, (Columns-1-i)*4+2);
	}

	drawPeaks();
}

GUISpectrum::~GUISpectrum()
{
}

bool GUISpectrum::process(SDL_Event * event)
{
	signed short * buffer;

	if ( event->type == SDL_USEREVENT ) {
		if ( event->user.code == GUI_OSCILLOSCOPE ) {
			clear();

			// Compute
			buffer = synth->getAnalyseBuffer();
			for ( int i = 0 ; i < Synth::analyseBufferSize ; i++ ) {
			}

			// Draw
			for ( int c = 0 ; c < Columns ; c++ ) {
				// Midi Note  21 (A0) = 27.5Hz
				// Midi Note 108 (C8) = 4186.0Hz
				// Shows From ~50Hz to ~4410Hz
				int index = powf(c+4, 2.85f)
					* (float)Synth::analyseBufferSize / 44100.0f;

				// Update peaks
				peaks[c] -= peakTime[c]/3;
				peakTime[c] += 2;
				if ( peaks[c] < 0 )
					peaks[c] = 0;
				else if ( peaks[c] >= 64 )
					peaks[c] = 63;
			}
			drawPeaks();

			return true;
		}
	}

	return false;
}

void GUISpectrum::drawColumn(int col, int height)
{
	unsigned int c = paletteColor(4);
	unsigned int * pixels = (unsigned int *) surface->pixels;

	if ( height < 0 )
		height = 0;
	else if ( height >= 64 )
		height = 63;

	pixels += col * (128/Columns) + 1 + (64-height)*128;
	for ( int i = height ; i > 0 ; i-- ) {
		for ( int i = (128/Columns - 2) ; i > 0 ; i-- )
			*pixels++ = c;
		pixels += 128 - (128/Columns - 2);
	}
}

void GUISpectrum::drawPeaks()
{
	unsigned int c = paletteColor(5);

	for ( int col = 0 ; col < Columns ; col++ ) {
		unsigned int * pix = (unsigned int *) surface->pixels;
		pix += col * (128/Columns) + 1 + (63 - peaks[col])*128;

		for ( int b = (128/Columns - 2) ; b > 0 ; b-- )
			*pix++ = c;
	}
}
