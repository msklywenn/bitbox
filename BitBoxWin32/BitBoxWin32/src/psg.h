#ifndef _PSG_H_
#define _PSG_H_

class PSG {
protected:
	signed short sample;
	int t;

	int volume;
	int invFrequency;

	int x;
	int duty;

public:
	PSG();

	void setDuty(int d) { duty = d; }
	void setVolume(int v) { volume = 0x7fff / 127 * v; }
	void setFrequency(int f) { invFrequency = 4410000 / f; t = 0.0f; sample = 0; }

	virtual void reset();
};

class Noise : public PSG {
	void reset();

public:
	Noise() { reset(); }

	signed short generate()
	{
		int carry;
	   
		carry = x & 1;
		x >>= 1;

		if ( carry ) {
			x = x ^ 0x6000;
			return -volume;
		} else {
			return volume;
		}
	}

	signed short compute()
	{
		t+=100;

		if ( t >= invFrequency ) {
			sample = generate();
			t -= invFrequency;
		}

		return sample;
	}

};

class WaveDuty : public PSG {
	void reset();

public:
	WaveDuty() { reset(); }

	// NDS Wave Duty
	// Each duty cycle consists of eight HIGH or LOW samples, so the sound
	// frequency is 1/8th of the selected sample rate. The duty cycle always
	// starts at the begin of the LOW period when the sound gets (re-)started.
	//
	// 0  12.5% "_______-_______-_______-"
	// 1  25.0% "______--______--______--"
	// 2  37.5% "_____---_____---_____---"
	// 3  50.0% "____----____----____----"
	// 4  62.5% "___-----___-----___-----"
	// 5  75.0% "__------__------__------"
	// 6  87.5% "_-------_-------_-------"
	// 7   0.0% "________________________"
	signed short generate()
	{
		x = (x+1)%8;

		if ( x <= duty )
			return -volume;
		else
			return volume;
	}

	signed short compute()
	{
		t+=100;

		if ( t >= invFrequency ) {
			sample = generate();
			t -= invFrequency;
		}

		return sample;
	}
};

#endif // _PSG_H_
