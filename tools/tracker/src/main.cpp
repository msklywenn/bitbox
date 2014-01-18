#include <SDL.h>

#include "font.h"
#include "palette.h"
#include "gui.h"
#include "guibutton.h"
#include "guichannel.h"
#include "guistatusbar.h"
#include "guitime.h"
#include "guiclock.h"
#include "guivalue.h"
#include "guiname.h"
#include "guimute.h"
#include "guioscilloscope.h"
#include "guispectrum.h"
#include "guivu.h"
#include "guiwaveout.h"
#include "tune.h"
#include "synth.h"
#include "copy.h"

#ifdef _WINDOWS
#include <windows.h>
#endif

Uint32 timer(Uint32 interval, void * param)
{
	Synth * synth = (Synth *) param;

	static int lastRow = -42;
	int currentRow = synth->getCurrentRow();
	if ( currentRow != lastRow ) {
		lastRow = currentRow;
		PushUserEvent(GUI_CURRENTROW, (void *)currentRow);
	}

	// Detect end of song and stop synth
	int end = 0;
	for ( int i = 0 ; i < 8 ; i++ )
		if ( currentRow > synth->getTune()->channels[i].lastRow 
				&& synth->getVolume(i) == 0 )
			end++;
		else
			break;
	if ( end == 8 )
		synth->stop(false);

	return interval;
}

bool fileExists(const char * filename)
{
	bool exists = false;
	FILE * f = fopen(filename, "rb");
	if ( f ) {
		exists = true;
		fclose(f);
	}
	return exists;
}

class Import : public Action
{
	Synth * synth;
	Tune * tune;
	GUI * gui;
	GUIStatusBar * status;
	GUIChannel * guichannels[8];
	GUIValue * guiRPM;
	GUIName * name;

	void job() {
		char str[256];
		sprintf(str, "Importing %s...", name->get());
		status->print(str);
		gui->render(status);
		if ( tune->Import(name->get()) ) {
			sprintf(str, "%s imported.", name->get());
			status->print(str);
		} else {
			sprintf(str, "ERROR : Failed importing %s.", name->get());
			status->print(str);
		}
		for ( int i = 0 ; i < 8 ; i++ )
			guichannels[i]->update();
		guiRPM->update();
		gui->render();
		synth->reset();
	}

public:
	Import(Synth * s, Tune * t, GUI * g, GUIStatusBar * gs, GUIChannel * gc[8], GUIValue * rpm, GUIName * n)
		: synth(s), tune(t), gui(g), status(gs), guiRPM(rpm), name(n)
	{
		for ( int i = 0 ; i < 8 ; i++ )
			guichannels[i] = gc[i];
	}
};

class Export : public Action
{ 
	Tune * tune;
	GUI * gui;
	GUIStatusBar * status;
	GUIChannel * guichannels[8];
	GUIValue * guiRPM;
	GUIName * name;

	void job() {
		char str[256];
		sprintf(str, "Exporting %s...", name->get());
		status->print(str);
		gui->render(status);
		if ( tune->Export(name->get()) ) {
			sprintf(str, "%s exported.", name->get()); 
			status->print(str);
		} else {
			sprintf(str, "ERROR : Failed exporting %s.", name->get());
			status->print(str);
		}
		gui->render();
	}

public:
	Export(Tune * t, GUI * g, GUIStatusBar * gs, GUIChannel * gc[8], GUIValue * rpm, GUIName * n)
		: tune(t), gui(g), status(gs), guiRPM(rpm), name(n)
	{
		for ( int i = 0 ; i < 8 ; i++ )
			guichannels[i] = gc[i];
	}
};

class Load : public Action
{
	Synth * synth;
	Tune * tune;
	GUI * gui;
	GUIName * name;
	GUIValue * guiRPM;
	GUIStatusBar * status;
	GUIChannel * guichannels[8];

	void job() {
		char str[256];
		sprintf(str, "Loading %s.txt...", name->get());
		status->print(str);
		gui->render(status);
		if ( tune->Load(name->get()) ) {
			sprintf(str, "%s.txt loaded.", name->get());
			status->print(str);
		} else {
			sprintf(str, "ERROR : Failed loading %s.", name->get());
			status->print(str);
		}
		for ( int i = 0 ; i < 8 ; i++ )
			guichannels[i]->update();
		guiRPM->update();
		gui->render();
		synth->reset();
	}

public:
	Load(Synth *s, Tune * t, GUI * gui, GUIName * name, GUIStatusBar * status, GUIValue * rpm, GUIChannel * ch[8])
		: synth(s), tune(t), gui(gui), name(name), guiRPM(rpm), status(status)
	{
		for ( int i = 0 ; i < 8 ; i++ )
			guichannels[i] = ch[i];
	}
};

class Save : public Action
{ 
	Tune * tune;
	GUI * gui;
	GUIName * name;
	GUIStatusBar * status;

	void job() {
		char str[256];
		sprintf(str, "Saving %s.txt...", name->get());
		status->print(str);
		gui->render(status);
		if ( tune->Save(name->get()) ) {
			sprintf(str, "%s.txt saved.", name->get());
			status->print(str);
		} else {
			sprintf(str, "ERROR : Failed saving %s.", name->get());
			status->print(str);
		}
		gui->render();
	}

public:
	Save(Tune * t, GUI * gui, GUIName * name, GUIStatusBar * status)
		: tune(t), gui(gui), name(name), status(status)
	{}
};

int main(int argc, char ** argv)
{
	SDL_Event event;
	bool running = true;
	static char str[256];
	memset(str, 0, 256);
	void (* query)(GUI *, GUIStatusBar *, Tune *, const char *, bool) = 0;

#ifdef _WINDOWS
#ifdef _DEBUG
	AllocConsole();
//	freopen("CONOUT$", "wb", stderr);
//	freopen("CONOUT$", "wb", stdout);
#endif	
#endif

	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);

	fontLoad();
	paletteLoad();

	Copy * copy = new Copy();

	GUI * gui = new GUI();

	Tune * tune = new Tune();
	Synth * synth = new Synth(tune);

	GUIChannel * guichannels[8];
	for ( int i = 0 ; i < 8 ; i++ ) {
		guichannels[i] = new GUIChannel(& tune->channels[i], i, copy, synth);
		gui->attach(guichannels[i]);
	}

	GUIStatusBar * status = new GUIStatusBar();
	gui->attach(status);

	gui->attach(new GUITime(synth));

	GUIValue * guiRPM = new GUIValue(567, 88, & tune->rpm, 100, 999);
	gui->attach(guiRPM);

	gui->attach(new GUIClock(tune));

	GUIName * name = new GUIName();
	gui->attach(name);

	gui->attach(new GUIWaveOut(synth, name, status));

	gui->attach(new GUIMute(synth));

	gui->attach(new GUIOscilloscope(synth));
	gui->attach(new GUISpectrum(synth));
	gui->attach(new GUIVU(synth));

	Load LoadAction(synth, tune, gui, name, status, guiRPM, guichannels);
	Save SaveAction(tune, gui, name, status);
	Import ImportAction(synth, tune, gui, status, guichannels, guiRPM, name);
	Export ExportAction(tune, gui, status, guichannels, guiRPM, name);
	gui->attach(new GUIButton(545, 33, 45, 10, &LoadAction));
	gui->attach(new GUIButton(545, 44, 45, 10, &SaveAction));
	gui->attach(new GUIButton(545, 55, 45, 10, &ImportAction));
	gui->attach(new GUIButton(545, 66, 45, 10, &ExportAction));

	gui->render();

	if ( ! SDL_AddTimer(100, timer, synth) )
		return 42;

	while ( running && SDL_WaitEvent(& event) ) {
		switch ( event.type ) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_VIDEORESIZE:
			case SDL_VIDEOEXPOSE:
				gui->render();
				break;
			case SDL_KEYDOWN:
				if ( event.key.keysym.sym == SDLK_ESCAPE ) { // Quit...
					running = false;
				} else if ( event.key.keysym.sym == SDLK_F3 ) {
					tune->clear();
					for ( int i = 0 ; i < 8 ; i++ )
						guichannels[i]->update();
					guiRPM->update();
					gui->render();
				} else if ( event.key.keysym.sym == SDLK_SPACE ) {
					synth->pause();
				} else if ( event.key.keysym.sym == SDLK_y && query ) {
					query(gui, status, tune, name->get(), true);
					query = 0;
				} else if ( event.key.keysym.sym == SDLK_n && query ) {
					query(gui, status, tune, name->get(), false);
					query = 0;
				} else {
					gui->process(& event);
				}
				break;
			default:
				gui->process(& event);
				break;
		}
	}

	delete synth;
	delete tune;
	delete gui;
	delete copy;

	paletteDestroy();
	fontDestroy();

	SDL_Quit();

#ifdef __WIN32__
#ifdef _DEBUG
	FreeConsole();
#endif
#endif

	return 0;
}
