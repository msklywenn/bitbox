#ifndef _GUIMESSAGE_H_
#define _GUIMESSAGE_H_

#include "guielement.h"

class GUIStatusBar : public GUIElement {
public:
	GUIStatusBar();
	void print(char * msg);
	inline void print(const char * msg) { print((char *) msg); }
	void printf(const char * msg, ...);
	bool process(SDL_Event * event);
};

#endif // _GUIMESSAGE_H_
