#include "gui.h"

GUI::GUI()
{
	screen = SDL_SetVideoMode(640, 480, 32, SDL_DOUBLEBUF|SDL_HWSURFACE);
	bg = SDL_LoadBMP("data/bg.bmp");
	SDL_BlitSurface(bg, 0, screen, 0);

	SDL_WM_SetCaption("Plop Tracker Version 0", "");
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY/4,
		   SDL_DEFAULT_REPEAT_INTERVAL);
}

GUI::~GUI()
{
	SDL_FreeSurface(screen);
	SDL_FreeSurface(bg);

	std::list<GUIElement *>::iterator it = elements.begin();
	while ( it != elements.end() ) {
		delete *it;
		++it;
	}
}

void GUI::attach(GUIElement * element)
{
	elements.push_back(element);
}

void GUI::render()
{
	SDL_BlitSurface(bg, 0, screen, 0);

	std::list<GUIElement *>::iterator it = elements.begin();
	while ( it != elements.end() ) {
		(*it)->render(screen);
		++it;
	}

	SDL_Flip(screen);
}

void GUI::render(GUIElement * element)
{
	SDL_BlitSurface(bg, element->getArea(), screen, element->getArea());
	element->render(screen);
	SDL_Flip(screen);
}

void GUI::fullscreen()
{
	int fullscreen = screen->flags & SDL_FULLSCREEN;

	SDL_FreeSurface(screen);

	if ( fullscreen )
		screen = SDL_SetVideoMode(640, 480, 32, SDL_DOUBLEBUF | SDL_HWSURFACE);
	else
		screen = SDL_SetVideoMode(640, 480, 32, 
				SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_FULLSCREEN);
}

void GUI::process(SDL_Event * event)
{
	if ( event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_F12 ) {
		fullscreen();
		render();
	} else {
		std::list<GUIElement *>::iterator it = elements.begin();
		while ( it != elements.end() ) {
			if ( (*it)->process(event) ) {
				SDL_BlitSurface(bg, (*it)->getArea(), screen, (*it)->getArea());
				(*it)->render(screen);
				SDL_Flip(screen);
			}
			++it;
		}
	}
}
