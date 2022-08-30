#include "synth.h"

#include <stdio.h>
#include <string.h>

#include "midi.h"

#ifdef USE_SDL
#include <SDL.h>
#else
#include <libdragon.h>
Synth* synth;
#endif

#if defined(USE_SDL)
void SynthStreamCallback(void* user, uint8_t* out, int len)
{
	Synth * synth = (Synth *) user;
	int samples = len / synth->SampleSize(); // len is bytes, we have 16b stereo
	synth->synth((signed short *) out, samples);
}
#else
void SynthStreamCallback(short* buffer, size_t numsamples)
{
	synth->synth(buffer, numsamples);
}
#endif

Synth::Synth(Tune* tune)
	: tune(tune), dRes(0.0f), dRow(0.0f), row(0), initialRow(0), analyseBufferPosition(0)
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
#else
	::synth = this; // look ma, garbage code! ...I DON'T CARE!
	audio_init(44100, 2);
	audio_set_buffer_callback(SynthStreamCallback);
#endif

	// Initialize PSGs
	for ( int i = 0 ; i < 6 ; i++ ) {
		channels[i].psg = new WaveDuty();
		channels[i].volume = 0;
		channels[i].mute = false;
	}
	for ( int i = 6 ; i < 8 ; i++ ) {
		channels[i].psg = new Noise();
		channels[i].volume = 0;
		channels[i].mute = false;
	}
}

Synth::~Synth()
{
#if defined(USE_SDL)
	if ( audioReady ) {
		SDL_CloseAudio();
	}
#else
	audio_close();
#endif
}

void Synth::readRow()
{
	for ( int i = 0 ; i < 8 ; i++ ) {
		if ( tune->channels[i].notes[row].active ) {
			channels[i].volume =
				tune->channels[i].notes[row].volume << 4;
			int freq = midiNoteToFrequency(tune->channels[i].notes[row].note);
			if ( i < 6 )
				freq *= 8;
			channels[i].psg->setFrequency(freq);
		}
	}
}

void Synth::synth(signed short* buffer, int samples, bool analyse)
{
	int left, right, s;

	for (int i = samples ; i > 0 ; i--) {
		// Playing
		if ( row < MAXROWS && dRes > 1.0f/(float)tune->resolution ) {
			dRow += 1.0f/((float)tune->resolution * 60.0f);
			if ( dRow > 1.0f/(float)tune->rpm && row < MAXROWS ) {
				readRow();
				row++;
				dRow = 0.0f;
			}
			// Linear enveloppe
			for ( int i = 0 ; i < 8 ; i++ ) {
				channels[i].volume -= tune->channels[i].dec;
				if ( channels[i].volume < 0 )
					channels[i].volume = 0;
				channels[i].psg->setVolume(channels[i].volume >> 2);
			}
			dRes = 0.0f;
		}

		// Mixing
		right = 0;
		for ( int i = 0 ; i < 8 ; i++ ) {
			s = channels[i].psg->compute(1.0f/44100.0f);
			if ( ! channels[i].mute )
				right += s;
		}

		// Clipping
		if ( right < -0x7FFF )
			right = -0x7FFF;
		else if ( right > 0x7FFF )
			right = 0x7FFF;

		// Filling
		left = right;
		*buffer++ = left;
		*buffer++ = right;

		dRes += 1.0f/44100.0f;
	}
}

void Synth::play()
{
	initialRow = row;
#if defined(USE_SDL)
	if ( audioReady )
		SDL_PauseAudio(0);
#else
	audio_pause(false);
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
	reset();
	if ( row < initialRow )
		row = initialRow;
}

void Synth::setRow(int l)
{
#ifdef USE_SDL
	bool p = audioReady && SDL_GetAudioStatus() == SDL_AUDIO_PLAYING;
#else
	bool p = true;
#endif

	if ( p )
		stop();
	row = l;
	if ( p )
		play();
}

void Synth::setChannelDuty(int ch, int duty)
{
	channels[ch].psg->setDuty(duty);
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

void Synth::reset()
{
	dRes = dRow = 0.0f;
	for ( int i = 0 ; i < 8 ; i++ ) {
		channels[i].psg->setVolume(0);
		channels[i].psg->setDuty(tune->channels[i].duty);
		channels[i].psg->reset();
		channels[i].volume = 0;
	}
}

unsigned int Synth::getVolume(int ch)
{
	if ( channels[ch].mute )
		return 0;

	signed short s = channels[ch].psg->getSample();
	if ( s < 0 )
		return -s;
	else
		return s;
}

bool Synth::waveOut(const char * filename)
{
	FILE * f = fopen(filename, "wb");
	if ( f == 0 )
		return false;

	// RIFF header
	fwrite("RIFF", 1, 4, f);
	fseek(f, 4, SEEK_CUR); // will write file size after writing data :)
	fwrite("WAVE", 1, 4, f);

	// FMT header
	fwrite("fmt ", 1, 4, f);
	static const int subChunk1Size = 16;
	fwrite(& subChunk1Size, 4, 1, f);
	static const short int format = 1; // PCM
	fwrite(& format, 2, 1, f);
	static const short int nbChannels = 2;
	fwrite(& nbChannels, 2, 1, f);
	static const int sampleRate = 44100;
	fwrite(& sampleRate, 4, 1, f);
	static const int byteRate = sampleRate * nbChannels * sizeof(short int);
	fwrite(& byteRate, 4, 1, f);
	static const short int blockAlign = nbChannels * sizeof(short int);
	fwrite(& blockAlign, 2, 1, f);
	static const short int bitsPerSample = 16;
	fwrite(& bitsPerSample, 2, 1, f);

	stop();
	int savedRow = row;
	row = 0;

	// DATA
	fwrite("data", 1, 4, f);
	fseek(f, 4, SEEK_CUR); // will write data size after writing data :)

	int dataSize = 0;
	bool finished = false;
	static signed short buffer[2048];
	while ( ! finished ) {
		synth(buffer, 2048, false);
		fwrite(buffer, 2, 2048 * nbChannels, f);
		dataSize += 2048 * nbChannels * sizeof(short);

		int end = 0;
		while ( end < 8 &&
				(row > tune->channels[end].lastRow && getVolume(end) == 0) )
			end++;
		if ( end == 8 )
			finished = true;
	}

	// Data size
	fseek(f, 40, SEEK_SET);
	fwrite(& dataSize, 4, 1, f);
	
	// File size
	dataSize += 36;
	fseek(f, 4, SEEK_SET);
	fwrite(& dataSize, 4, 1, f);

	fclose(f);

	row = savedRow;

	return true;
}
