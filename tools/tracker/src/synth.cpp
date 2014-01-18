#include "synth.h"

#include <stdio.h>
#include <string.h>
#include <SDL.h>

#include "midi.h"
#include "guievents.h"

int SynthStreamCallback(const void * in, void * out, unsigned long frames,
		const PaStreamCallbackTimeInfo * timeInfo, PaStreamCallbackFlags status,
		void * user)
{
	Synth * synth = (Synth *) user;
	synth->synth((signed short *) out, frames);
	return 0;
}

Synth::Synth(Tune * tune)
	: stream(0), tune(tune), dRes(0.0f), dRow(0.0f),
	row(0), initialRow(0), latency(0.0), analyseBufferPosition(0)
{
	// Initialize PortAudio
	PaError code;

	code = Pa_Initialize();
	if ( code != paNoError )
		printf("PortAudio error : %s\n", Pa_GetErrorText(code));

#ifdef _WINDOWS
	// Find device with lowest latency
	const PaDeviceInfo * deviceInfo;
	PaDeviceIndex device = -1;
	for ( PaDeviceIndex i = 0 ; i < Pa_GetDeviceCount() ; i++ ) {
		deviceInfo = Pa_GetDeviceInfo(i);
		if ( device == -1 ||
			( deviceInfo->defaultLowOutputLatency < Pa_GetDeviceInfo(device)->defaultLowOutputLatency
				&& deviceInfo->maxOutputChannels >= 2 ) )
			device = i;
	}
	// Open device
	PaStreamParameters param;
	memset(& param, 0, sizeof(PaStreamParameters));
	param.channelCount = 2;
	param.device = device;
	param.hostApiSpecificStreamInfo = 0;
	param.sampleFormat = paInt16;
	param.suggestedLatency = Pa_GetDeviceInfo(device)->defaultLowOutputLatency;
	code = Pa_OpenStream(& stream, 0, & param, 44100.0, 512, paNoFlag, SynthStreamCallback, this);
	if ( code != paNoError )
		fprintf(stderr, "PortAudio error : %s\n", Pa_GetErrorText(code));
#else
	Pa_OpenDefaultStream(& stream, 0, 2, paInt16, 44100.0, 512,
			SynthStreamCallback, this);
#endif

	if ( ! stream )
		fprintf(stderr, "Could not init PortAudio\n");

#ifdef _DEBUG
	if ( stream )
		latency = Pa_GetStreamInfo(stream)->outputLatency;
	fprintf(stderr, "Device latency : %fs.\n", latency);
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
	if ( stream ) {
		Pa_CloseStream(stream);
		Pa_Terminate();
	}
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

void Synth::synth(signed short * buffer, int samples, bool analyse)
{
	int left, right, s;

	for ( int i = samples ; i > 0 ; i-- ) {
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

		if ( analyse ) {
			analyseBuffer[analyseBufferPosition++] = right;
			if ( analyseBufferPosition == analyseBufferSize ) {
				PushUserEvent(GUI_OSCILLOSCOPE);
				analyseBufferPosition = 0;
			}
		}

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
	if ( stream )
		Pa_StartStream(stream);
}

void Synth::pause()
{
	if ( stream && Pa_IsStreamActive(stream) )
		stop();
	else
		play();
}

void Synth::stop(bool abort)
{
	if ( stream ) {
		if ( abort )
			Pa_AbortStream(stream);
		else
			Pa_StopStream(stream);
	}
	reset();
	row -= (unsigned int)(latency / 60.0f * tune->rpm);
	if ( row < initialRow )
		row = initialRow;
}

void Synth::setRow(int l)
{
	bool p = stream && Pa_IsStreamActive(stream);

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
	if ( stream && Pa_IsStreamActive(stream) ) {
		int r = (int)(row - latency / 60.0f * tune->rpm);
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
