#include "../src/shared.h"
#include "../src/synth.h"
#include "platform.h"

void* platform_start()
{
	debug_init_isviewer();
	debug_init_usblog();
	display_init(RESOLUTION_640x480, DEPTH_16_BPP, 1,
			GAMMA_NONE, ANTIALIAS_RESAMPLE_FETCH_ALWAYS);
	gl_init();
	audio_init(44100, 4);
    timer_init();
    return NULL;
}

bool platform_swap()
{
    gl_swap_buffers();
    return true;
}

void platform_audio(Synth* synth)
{
	while (audio_can_write())
	{
		short* buf = audio_write_begin();
		synth->synth(buf, audio_get_buffer_length());
		audio_write_end();
	}
}

long long platform_ticks()
{
    return TIMER_MICROS_LL(timer_ticks()) / 1000;
}

void platform_end(void*)
{
}

