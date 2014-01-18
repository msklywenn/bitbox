#include "channel.h"

Channel::Channel()
{
	reset();
}

void Channel::reset()
{
	duty = 0;
	dec = 4;
	for ( int i = 0 ; i < MAXROWS ; i++ ) {
		notes[i].volume = 10;
		notes[i].note = 60;
		notes[i].active = false;
	}
	lastRow = 0;
}

void Channel::setNote(int pos, int volume, int note)
{
	notes[pos].volume = volume;
	notes[pos].note = note;
	notes[pos].active = true;

	if ( pos > lastRow )
		lastRow = pos;
}

void Channel::deleteNote(int pos)
{
	notes[pos].active = false;
	if ( pos == lastRow )
		while ( lastRow > 0 && notes[lastRow].active == false )
			lastRow--;
}
