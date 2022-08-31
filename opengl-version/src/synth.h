#ifndef _SYNTH_H_
#define _SYNTH_H_

#include "tune.h"
#include "psg.h"

class Synth {
	bool audioReady;

	Tune * tune;

	struct Channel {
		int volume;
	};

	WaveDuty square[6];
	Noise noise[2];
	Channel channels[8];
	float dRes, dRow;
	unsigned int row, initialRow;
	int sampleSize;

	void readRow();

public:
	Synth(Tune * tune);
	~Synth();

	void play();
	void stop(bool abort = true);
	void pause();

	unsigned int getCurrentRow();

	void synth(signed short * samples, int count);

	Tune * getTune() { return tune; }

	const int SampleSize() const { return sampleSize; }
};

#endif // _SYNTH_H_
