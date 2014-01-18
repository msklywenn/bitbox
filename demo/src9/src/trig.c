#include "trig.h"
#include <nds.h>

int uber_sin(int x)
{
	// TODO this may be simplified
	x = 4096 - (x & 0x1FFF);
	int ax = x;
	if ( ax < 0 )
		ax = -ax;
	return 4 * x - ((4 * x * ax) >> 12);
}