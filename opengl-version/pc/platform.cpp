#include "../src/shared.h"
#include "platform.h"

void* platform_start()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 1);
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 2);
	SDL_Surface * screen = SDL_SetVideoMode(WIDTH, HEIGHT, 16,
			SDL_DOUBLEBUF|SDL_HWSURFACE|SDL_OPENGL);
	SDL_WM_SetCaption("BitBox - Winport", "BitBox - Winport");
    
    return screen;
}

bool platform_swap()
{
    SDL_GL_SwapBuffers();

    bool running = true;
    SDL_Event event;
    while ( SDL_PollEvent(& event) )
    {
        switch ( event.type ) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                if ( event.key.keysym.sym == SDLK_ESCAPE ) // Quit...
                    running = false;
                break;
            default:
                break;
        }
    }

    return running;
}

void platform_audio(Synth* synth)
{
}

long long platform_ticks()
{
    return SDL_GetTicks();
}

void platform_end(void* screen)
{
	SDL_FreeSurface((SDL_Surface*)screen);
	SDL_Quit();
}

