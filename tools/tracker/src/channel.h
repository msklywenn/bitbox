#ifndef _CHANNEL_H_
#define _CHANNEL_H_

#define MAXROWS 2048

struct Note {
	int volume;
	int note; // midi note number
	bool active;
};

struct Channel {
	int duty;
	int dec;
	Note notes[MAXROWS];

	int lastRow;

	Channel();

	void reset();

	void setNote(int pos, int volume, int note);
	void setNote(int pos, Note & note) { setNote(pos, note.volume, note.note); }
	void deleteNote(int pos);
};

#endif // _CHANNEL_H_
