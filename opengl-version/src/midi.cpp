#include "midi.h"
#include "math.h"
#include <stdio.h>

#ifdef _WINDOWS
int round(float f)
{
	return (int) (f + 0.5f);
}
#endif

int midiNoteToFrequency(int note)
{
	return (int) (440.0f * pow(2.0f, (note - 69)/12.0f));
}

int midiFrequencyToNote(int freq)
{
	return round(69.0f + log(freq/440.0f)*17.31234f);
}

char * midiNoteName(int note)
{
	static char str[4];

	int l = note % 12;

	str[0] = "CCDDEFFGGAAB"[l];

	if ( l == 1 || l == 3 || l == 6	|| l == 8 || l == 10 )
		str[1] = '#';
	else
		str[1] = ' ';

	int octave = (note - 12) / 12;
	if ( note < 12 )
		str[2] = '-';
	else
		str[2] = '0' + octave;

	return str;
}
