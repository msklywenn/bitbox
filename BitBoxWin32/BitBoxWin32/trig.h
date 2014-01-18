#ifndef _TRIG_H_
#define _TRIG_H_

#ifdef __cplusplus
extern "C" {
#endif

// approximation of sin with pi=4096
//
// pi-(x mod 2pi) then
// 4.x - 4.x.|x|
int uber_sin(int x);
#define uber_cos(x) uber_sin(x + 0x800)

// Conversion from old cos/sin to new uber cos/sin
// The old was working with real value of pi in fixed point 12 (pi = 12867)
// while the new one uses pi = 4096
#define sin(x) uber_sin((((x) * 325) >> 10))
#define cos(x) uber_cos((((x) * 325) >> 10))

#ifdef __cplusplus
}
#endif

#endif // _TRIG_H_