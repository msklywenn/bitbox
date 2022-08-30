#include "psg.h"

PSG::PSG()
	: sample(0), t(0.0f), volume(0), invFrequency(0), duty(0)
{
}

void PSG::reset()
{
	t = 0.0f;
	sample = 0;
}

// NDS PSG Noise
// X=X SHR 1, IF carry THEN Out=LOW, X=X XOR 6000h ELSE Out=HIGH

void Noise::reset()
{
	x = 0x7FFF;
	PSG::reset();
}


void WaveDuty::reset()
{
	x = 0;
	PSG::reset();
}
