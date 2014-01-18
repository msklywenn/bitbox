#ifndef _PSG_H_
#define _PSG_H_

class PSG {
	signed short sample;
	float t;

	int volume;
	int frequency;

protected:
	int x;
	int duty;

	virtual signed short generate() = 0;

public:
	PSG();

	void setDuty(int d) { duty = d; }
	void setVolume(int v) { volume = v; }
	void setFrequency(int f) { frequency = f; t = 0.0f; sample = 0; }

	virtual void reset();

	signed short compute(float time);

	signed short getSample() const { return sample; }
};

class Noise : public PSG {
	signed short generate();
	void reset();

public:
	Noise() { reset(); }
};

class WaveDuty : public PSG {
	signed short generate();
	void reset();

public:
	WaveDuty() { reset(); }
};

#endif // _PSG_H_
