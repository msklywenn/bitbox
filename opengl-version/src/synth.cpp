#include "synth.h"

#include <stdio.h>
#include <string.h>

#include "midi.h"

#ifdef USE_SDL
#include <SDL.h>
#else
#include <libdragon.h>
#endif

#if defined(USE_SDL)
void SynthStreamCallback(void* user, uint8_t* out, int len)
{
	Synth * synth = (Synth *) user;
	int samples = len / synth->SampleSize(); // len is bytes, we have 16b stereo
	synth->synth((signed short *) out, samples);
}
#endif

int midi2freq[128];

Synth::Synth(Tune* tune)
	: tune(tune), dRes(0.0f), dRow(0.0f), row(0), initialRow(0)
{
#if defined(USE_SDL)
	SDL_AudioSpec wanted;
	wanted.freq = 44100;
	wanted.format = AUDIO_S16;
	wanted.channels = 2;
	wanted.samples = 1024;
	wanted.callback = SynthStreamCallback;
	wanted.userdata = this;

	SDL_AudioSpec obtained;
	audioReady = SDL_OpenAudio(&wanted, &obtained) == 0;
	if (!audioReady) {
		fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
		return;
	}

	sampleSize = obtained.channels * (obtained.format & 0xFF) / 8;
#endif

	for (int i = 0; i < 128; i++)
		midi2freq[i] = midiNoteToFrequency(i);

	// Initialize PSGs
	for ( int i = 0 ; i < 8 ; i++ ) {
		channels[i].volume = 0;
	}
}

Synth::~Synth()
{
#if defined(USE_SDL)
	if ( audioReady ) {
		SDL_CloseAudio();
	}
#endif
}

void Synth::readRow()
{
	for ( int i = 0 ; i < 8 ; i++ ) {
		if ( tune->channels[i].notes[row].active ) {
			channels[i].volume =
				tune->channels[i].notes[row].volume << 4;
			int freq = midi2freq[tune->channels[i].notes[row].note];
			if (i < 6)
				square[i].setFrequency(freq*8);
			else
				noise[i-6].setFrequency(freq);
		}
	}
}

void Synth::synth(signed short* buffer, int samples)
{
	float invFreq = 1.0f / 44100.0f;
	float invRes = 1.0f / tune->resolution;
	float invRes60 = 1.0f / (tune->resolution * 60.0f);
	float invRPM = 1.0f / tune->rpm;

	for (int i = samples ; i > 0;)
	{
		// Playing
		if (dRes > invRes)
		{
			dRow += invRes60;
			if (dRow > invRPM && row < MAXROWS)
			{
				readRow();
				row++;
				dRow = 0.0f;
			}
			// Linear enveloppe
			for (int i = 0 ; i < 8 ; i++)
			{
				channels[i].volume -= tune->channels[i].dec;
				if ( channels[i].volume < 0 )
					channels[i].volume = 0;
			}
			square[0].setVolume(channels[0].volume >> 2);
			square[1].setVolume(channels[1].volume >> 2);
			square[2].setVolume(channels[2].volume >> 2);
			square[3].setVolume(channels[3].volume >> 2);
			square[4].setVolume(channels[4].volume >> 2);
			square[5].setVolume(channels[5].volume >> 2);
			noise[0].setVolume(channels[6].volume >> 2);
			noise[1].setVolume(channels[7].volume >> 2);
			dRes = 0.0f;
		}

		int samplesToTick = (int)((invRes - dRes) / invFreq);
		if (samplesToTick <= 0) samplesToTick = 1;
		if (samplesToTick > i) samplesToTick = i;
		for (int j = samplesToTick; j > 0; j--)
		{
			// Mixing
			int sample = square[0].compute()
				+ square[1].compute()
				+ square[2].compute()
				+ square[3].compute()
				+ square[4].compute()
				+ square[5].compute()
				+ noise[0].compute()
				+ noise[1].compute();

			// Clipping
			if (sample < -0x7FFF) sample = -0x7FFF;
			else if (sample > 0x7FFF) sample = 0x7FFF;

			// Filling
			*buffer++ = sample;
			*buffer++ = sample;
			i--;
		}

		dRes += samplesToTick * invFreq;
	}
}

void Synth::play()
{
	initialRow = row;
#if defined(USE_SDL)
	if ( audioReady )
		SDL_PauseAudio(0);
#endif
}

void Synth::pause()
{
	if ( audioReady )
	{
#ifdef USE_SDL
		if (SDL_GetAudioStatus() == SDL_AUDIO_PLAYING)
			SDL_PauseAudio(1);
		else
			SDL_PauseAudio(0);
#endif
	}
}

void Synth::stop(bool abort)
{
#ifdef USE_SDL
	if ( audioReady ) {
		if (abort)
			SDL_CloseAudio();
		else
			SDL_PauseAudio(1);
	}
#endif
	if ( row < initialRow )
		row = initialRow;
}

unsigned int Synth::getCurrentRow()
{
#ifdef USE_SDL
	bool p = audioReady && SDL_GetAudioStatus() == SDL_AUDIO_PLAYING;
#else
	bool p = true;
#endif
	if (p) {
		int r = row;
		if ( r < (int) initialRow )
			return initialRow;
		return r;
	}

	return row;
}
