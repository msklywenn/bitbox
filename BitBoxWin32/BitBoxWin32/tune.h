#ifndef _TUNE_H_
#define _TUNE_H_

#include "channel.h"

struct Tune {
	Channel channels[8];
	int resolution;
	int rpm; // rows per minute

	Tune() { clear(); }

	// To text format used by the tracker
	bool Save(const char * filename);
	bool Load(const char * filename);
	bool LoadText(const char* txt);

	// To binary format used by the NDS player
	// XXX FUCKED UP ! XXX
	bool Export(const char * filename);
	bool Import(const char * filename);

	void clear();
};

#endif // _TUNE_H_
