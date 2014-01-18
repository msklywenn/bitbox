#include "guivu.h"

#include <math.h>

#include "palette.h"

GUIVU::GUIVU(Synth * s)
	: GUIElement(502, 109, 128, 64), synth(s)
{
	for ( int i = 0 ; i < Columns ; i++ ) {
		peaks[i] = 0;
		peakTime[i] = 0;
	}

	drawPeaks();
}

bool GUIVU::process(SDL_Event * event)
{
	if ( event->type == SDL_USEREVENT ) {
		if ( event->user.code == GUI_OSCILLOSCOPE ) {
			clear();

			int total = 0;

			for ( int c = 0 ; c < 8 ; c++ ) {
				int m = synth->getVolume(c);
				int m_gfx = m * 64 / 0x7FFF;
				drawColumn(c+2, m_gfx);

				// Update peaks
				peaks[c+2] -= peakTime[c+2]/3;
				peakTime[c+2] += 2;
				if ( m_gfx > peaks[c+2] ) {
					peaks[c+2] = m_gfx;
					peakTime[c+2] = 0;
				}
				if ( peaks[c+2] < 0 )
					peaks[c+2] = 0;
				else if ( peaks[c+2] >= 64 )
					peaks[c+2] = 63;

				total += m;
			}

			int total_gfx = total * 64 / 0x7FFF;
			drawColumn(0, total_gfx);

			// Update peaks
			peaks[0] -= peakTime[0]/3;
			peakTime[0] += 2;
			if ( total_gfx > peaks[0] ) {
				peaks[0] = total_gfx;
				peakTime[0] = 0;
			}
			if ( peaks[0] < 0 )
				peaks[0] = 0;
			else if ( peaks[0] >= 64 )
				peaks[0] = 63;

			drawPeaks();

			return true;
		}
	}

	return false;
}

void GUIVU::drawColumn(int col, int height)
{
	unsigned int c = paletteColor(4);
	unsigned int * pixels = (unsigned int *) surface->pixels;

	if ( height < 0 )
		height = 0;
	else if ( height >= 64 ) {
		height = 63;
		c = paletteColor(7);
	}

	pixels += col * (128/Columns) + 1 + (64-height)*128 + (128%Columns)/2;
	for ( int i = height ; i > 0 ; i-- ) {
		for ( int i = (128/Columns - 2) ; i > 0 ; i-- )
			*pixels++ = c;
		pixels += 128 - (128/Columns - 2);
	}
}

void GUIVU::drawPeaks()
{
	unsigned int c = paletteColor(5);

	for ( int col = 0 ; col < Columns ; col++ ) {
		if ( col == 1 )
			continue;
		unsigned int * pix = (unsigned int *) surface->pixels;
		pix += col * (128/Columns) + 1 + (63 - peaks[col])*128
			+ (128%Columns)/2;

		for ( int b = (128/Columns - 2) ; b > 0 ; b-- )
			*pix++ = c;
	}
}
