#ifndef _GUICHANNEL_H_
#define _GUICHANNEL_H_

#include "guielement.h"
#include "channel.h"
#include "copy.h"
#include "synth.h"

class GUIChannel : public GUIElement {
	static const int DELTA = 15;
	static const int EDITDUTY = -2;
	static const int EDITDEC = -3;

	Channel * channel;
	int number;
	int offset;
	int selectBegin, selectEnd;
	int x, y;
	bool mousedown;
	bool shift;
	Note lastNote;

	Copy * copy;
	Synth * synth;

public:
	GUIChannel(Channel *, int number, Copy *, Synth *);

	void update();

	bool process(SDL_Event * event);
};

#endif // _GUICHANNEL_H_
