#ifndef _SYNTH_H_
#define _SYNTH_H_

#include <portaudio.h>

#include "tune.h"
#include "psg.h"

class Synth {
	PaStream * stream;

	Tune * tune;

	struct Channel {
		PSG * psg;
		int volume;
		bool mute;
	};

	Channel channels[8];
	float dRes, dRow;
	unsigned int row, initialRow;
	PaTime latency;

	void readRow();

public:
	static const int analyseBufferSize = 4096;
private:
	int analyseBufferPosition;
	signed short analyseBuffer[analyseBufferSize];

public:
	Synth(Tune * tune);
	~Synth();

	void play();
	void stop(bool abort = true);
	void pause();

	bool toggleMute(int channel)
		{ return channels[channel].mute = ! channels[channel].mute; }
	void setRow(int l);
	void setChannelDuty(int channel, int duty);

	unsigned int getCurrentRow();
	unsigned int getVolume(int channel);

	void synth(signed short * samples, int count, bool analyse = true);

	signed short * getAnalyseBuffer() { return analyseBuffer; }

	void reset();

	Tune * getTune() { return tune; }

	bool waveOut(const char * filename);
};

#endif // _SYNTH_H_
