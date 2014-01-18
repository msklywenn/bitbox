#ifndef _GUICLOCK_H_
#define _GUICLOCK_H_

#include "guielement.h"
#include "tune.h"

class GUIClock : public GUIElement {
	Tune * tune;
public:
	GUIClock(Tune *);
	bool process(SDL_Event * event);
};

#endif // _GUICLOCK_H_
