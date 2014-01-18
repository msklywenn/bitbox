#include "psg.h"

PSG::PSG()
	: sample(0), t(0.0f), volume(0), frequency(0), duty(0)
{
}

signed short PSG::compute(float time)
{
	t += time;

	if ( t >= 1.0f/(float)frequency ) {
		sample = generate() * volume / 127;
		t -= 1.0f/(float)frequency;
	}

	return sample;
}

void PSG::reset()
{
	t = 0.0f;
	sample = 0;
}

// NDS PSG Noise
// X=X SHR 1, IF carry THEN Out=LOW, X=X XOR 6000h ELSE Out=HIGH
signed short Noise::generate()
{
	int carry;
   
	carry = x & 1;
	x >>= 1;

	if ( carry ) {
		x = x ^ 0x6000;
		return -0x7FFF;
	} else {
		return 0x7FFF;
	}
}

void Noise::reset()
{
	x = 0x7FFF;
	PSG::reset();
}

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
signed short WaveDuty::generate()
{
	x = (x+1)%8;

	if ( x <= duty )
		return -0x7FFF;
	else
		return 0x7FFF;
}

void WaveDuty::reset()
{
	x = 0;
	PSG::reset();
}
