#include <stdio.h>
#include <math.h>

char * midiNoteName(int note)
{
	static char str[4];
	if ( note < 0 || note > 127 ) {
		sprintf(str, "INV");
		return str;
	}

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

#if _WIN32
int round(float f)
{
	return (int)(f+0.5);
}
#endif

int midiFreqToNote(unsigned short freq)
{
	return round(69.0 + log(freq/440.0)*17.31234 );
}

#pragma pack(1)

struct NDSNote {
	unsigned int time : 13;
	unsigned int volume : 5;
	unsigned int freq : 14;
#if _WIN32
};
#else
} __attribute__((packed));
#endif

#include <assert.h>

int main(int argc, char ** argv)
{
	assert(sizeof(NDSNote) == 4);

	if ( argc == 2 ) {
		NDSNote note;
		sscanf(argv[1], "%x", (unsigned int *) & note);
		printf(">> time(%d) volume(%d) note(%s) [%dHz -> %d]\n",
				note.time, note.volume,
				midiNoteName(midiFreqToNote(note.freq)), note.freq,
				midiFreqToNote(note.freq) );
		return 0;
	}
	printf("Give me 32 bit hex of a nds note, I give you what it means\n");
	return 1;
}
