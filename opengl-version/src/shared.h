#ifndef _SHARED_H_
#define _SHARED_H_

class Synth;

#define WIDTH 640
#define HEIGHT 480

void* platform_start();
bool platform_swap();
void platform_audio(Synth* synth);
long long platform_ticks();
void platform_end(void*);

#endif // _SHARED_H_
