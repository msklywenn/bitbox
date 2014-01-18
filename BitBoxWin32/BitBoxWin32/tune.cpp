#include "tune.h"
#include "midi.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

struct NDSChannel {
	unsigned int timer;
	unsigned int volume;
	unsigned int duty;
	unsigned int dec;
	int notes_offset;
};

#ifdef _WINDOWS
#pragma pack(push, 1)
#endif

struct NDSNote {
	unsigned int time : 13;
	unsigned int volume : 5;
	unsigned int frequency : 14;
#ifdef _WINDOWS
};
#else
} __attribute__((packed));
#endif

#ifdef _WINDOWS
#pragma pack(pop)
#endif

void writeNote(int time, int volume, int frequency, FILE * f)
{
	NDSNote tmpNote = { time, volume, frequency };
	fwrite(& tmpNote, sizeof(NDSNote), 1, f);

#ifdef _DEBUG
	printf("N time(%4d) volume(%2d) frequency(%8d)\n", time, volume, frequency);
#endif
}

int iceilf(float f)
{
	return (int)f + 1;
}

bool Tune::Export(const char * filename)
{
	assert(sizeof(NDSChannel) == 20);

	NDSChannel tmpChannel;
	int nbNotes[8];

	int notes_offset = (sizeof(NDSChannel) * 8)/4;

	FILE * file = fopen(filename, "wb");
	
	if ( file == 0 )
		return false;

	memset(nbNotes, 0, sizeof(int) * 8);

	// Jump over channels header, will be written after
	fseek(file, sizeof(NDSChannel) * 8, SEEK_SET);

#ifdef _DEBUG
	int dummies = 0;
#endif

	int framesPerRow = iceilf(1.0f/((float)rpm/60.0f/(float)resolution));

	// Write notes
	for ( int i = 0 ; i < 8 ; i++ ) {
		int rows = 0;
		for ( int j = 0 ; j < MAXROWS ; j++ ) {
			if ( channels[i].notes[j].active ) {
				int time = rows * framesPerRow;
				while ( time > 8191 ) { // output dummy notes to avoid overflows
					writeNote(8191, 0, 1, file);
					time -= 8191;
					nbNotes[i]++;
#ifdef _DEBUG
					dummies++;
#endif
				}
				writeNote(time, channels[i].notes[j].volume,
						midiNoteToFrequency(channels[i].notes[j].note), file);
				nbNotes[i]++;
				rows = 0;
			}
			rows++;
		}
		// End of track note
		writeNote(0, 0, 0, file);
		nbNotes[i]++;
	}

#ifdef _DEBUG
	printf("Exporting '%s' created %d dummy notes.\n", filename, dummies);
#endif

	fseek(file, 0, SEEK_SET);

	// Write channels (header)
	for ( int i = 0 ; i < 8 ; i++ ) {
		tmpChannel.timer = 0;
		tmpChannel.volume = 0;
		tmpChannel.duty = channels[i].duty<<24;
		tmpChannel.dec = channels[i].dec;
		tmpChannel.notes_offset = notes_offset;
		fwrite(& tmpChannel, sizeof(NDSChannel), 1, file);

		notes_offset += nbNotes[i];
	}

	fclose(file);

	return true;
}

bool Tune::Import(const char * filename)
{
	// XXX //
	return false;
	// XXX //

	NDSChannel tmpChannel;
	NDSNote tmpNote;

	FILE * file = fopen(filename, "rb");

	if ( file == 0 )
		return false;

	fread(& resolution, 2, 1, file);
	fread(& rpm, 2, 1, file);

	// Reset everything and read channels
	for ( int i = 0 ; i < 8 ; i++ ) {
		channels[i].reset();
		fread(& tmpChannel, sizeof(NDSChannel), 1, file);
		channels[i].duty = tmpChannel.duty;
		channels[i].dec = tmpChannel.dec;
	}

	// Read notes
	for ( int i = 0 ; i < 8 ; i++ ) {
		int row = 0;
		do {
			fread(& tmpNote, sizeof(NDSNote), 1, file);
			if ( tmpNote.time != 0 ) {
				row += (int)((float)(tmpNote.time - 1) / (float)resolution
					/ 60.0f * (float)rpm);
				if ( tmpNote.frequency != 0 )
					channels[i].notes[row].active = true;
				channels[i].notes[row].volume = tmpNote.volume;
				channels[i].notes[row].note
					= midiFrequencyToNote(tmpNote.frequency);
				channels[i].lastRow = row;
				row++;
			}
		} while ( tmpNote.time != 0 );
	}

	return true;
}

bool Tune::Save(const char * filename)
{
	char _filename[256];
	strcpy(_filename, filename);
	strcat(_filename, ".txt");

	FILE * f = fopen(_filename, "wb");

	if ( f == 0 ) {
		return false;
	}

	fprintf(f, "%d\n", rpm);

	for ( int i = 0 ; i < 8 ; i++ )
		fprintf(f, "%d %d\n", channels[i].duty, channels[i].dec);

	for ( int i = 0 ; i < 8 ; i++ ) {
		for ( int j = 0 ; j < MAXROWS ; j++ ) {
			if ( channels[i].notes[j].active ) {
				fprintf(f, "%d %d %d %d\n", i, j,
						channels[i].notes[j].volume,
						channels[i].notes[j].note);
			}
		}
	}

	fclose(f);

	return true;
}

bool Tune::Load(const char * filename)
{
	char _filename[256];
	strcpy(_filename, filename);
	strcat(_filename, ".txt");

	FILE * f = fopen(_filename, "rb");

	clear();

	if ( f == 0 ) {
		return false;
	}

	if ( fscanf(f, "%d\n", &rpm) != 1 )
		goto error;
	
	int framesPerRow = iceilf(1.0f/((float)rpm/60.0f/(float)resolution));
	rpm = framesPerRow * 60;

	for ( int i = 0 ; i < 8 ; i++ )
		if ( fscanf(f, "%d %d\n", &(channels[i].duty), &(channels[i].dec)) != 2 )
			goto error;

	int c, r, v, n;
	while ( fscanf(f, "%d %d %d %d\n", &c, &r, &v, &n) == 4 ) {
		channels[c].notes[r].volume = v;
		channels[c].notes[r].note = n;
		channels[c].notes[r].active = true;
		if ( channels[c].lastRow < r )
			channels[c].lastRow = r;
	}

	fclose(f);

	return true;

error:
	fclose(f);
	return false;
}

void Tune::clear()
{
	resolution = 60;
	rpm = 280;
	for ( int i = 0 ; i < 8 ; i++ )
		channels[i].reset();
}
