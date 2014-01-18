#include <nds.h>

#include "options.h"
#include "trig.h"
#include "3D.h"

#define FADES 1 // ~128 bytes... (packed)

#if FADES
#define BRIGHT (1<<14)
#define DARK (2<<14)

int fade_current = 31 << 2; // starts white
int fade_target = 16 << 2;
#endif

u32 cubelist[] =
{
	COMMAND(CDIFAMB, CBEGIN, CNORMAL, CVERTEX),
	DIFAMB(RGB15(16, 16, 16), RGB15(8, 8, 8)),
	QUAD,
	NORMAL(0, 512, 0),
	VERTEX(-64,-64,-64),

	COMMAND(CVERTEX, CVERTEX, CVERTEX, CNORMAL),
	VERTEX( 64,-64,-64),
	VERTEX( 64,-64, 64),
	VERTEX(-64,-64, 64),
	NORMAL(0, 511, 0),

	COMMAND(CVERTEX, CVERTEX, CVERTEX, CVERTEX),
	VERTEX(-64, 64,-64),
	VERTEX(-64, 64, 64),
	VERTEX( 64, 64, 64),
	VERTEX( 64, 64,-64),

	COMMAND(CNORMAL, CVERTEX, CVERTEX, CVERTEX),
	NORMAL(512, 0, 0),
	VERTEX(-64,-64,-64),
	VERTEX(-64,-64, 64),
	VERTEX(-64, 64, 64),

	COMMAND(CVERTEX, CNORMAL, CVERTEX, CVERTEX),
	VERTEX(-64, 64,-64),
	NORMAL(511, 0, 0),
	VERTEX( 64,-64,-64),
	VERTEX( 64, 64,-64),

	COMMAND(CVERTEX, CVERTEX, CNORMAL, CVERTEX),
	VERTEX( 64, 64, 64),
	VERTEX( 64,-64, 64),
	NORMAL( 0, 0, 512),
	VERTEX(-64,-64,-64),

	COMMAND(CVERTEX, CVERTEX, CVERTEX, CNORMAL),
	VERTEX(-64, 64,-64),
	VERTEX( 64, 64,-64),
	VERTEX( 64,-64,-64),
	NORMAL( 0, 0, 511),

	COMMAND(CVERTEX, CVERTEX, CVERTEX, CVERTEX),
	VERTEX(-64,-64, 64),
	VERTEX( 64,-64, 64),
	VERTEX( 64, 64, 64),
	VERTEX(-64, 64, 64),
};
#define cube() call_list(cubelist, sizeof(cubelist)/sizeof(u32))

u32 initlist[] =
{
	COMMAND(CVIEWPORT, CMTXMODE, CMTXLOAD4x4, 0),
	VIEWPORT(0, 0, 255, 191), // full screen
	PROJECTION, // matrix mode
	// Projection matrix Perspective(fov=50°, near=0.1, far=40, ratio=1.33)
	6587, 	0, 	0,	0,
	0, 	8783, 	0,	0,
	0, 	0, 	-4116,	-4096,
	0, 	0, 	-821,	0,

	COMMAND(CMTXMODE, CMTXIDENTITY, CLIGHTVECTOR, CLIGHTCOLOR),
	MODELVIEW, // matrix mode
	NORMAL(-96, -144, -482), // light vector
	RGB15(31, 31, 31), // light color
};
#define init() call_list(initlist, sizeof(initlist)/sizeof(u32))

void rotate(int angle, int v)
{
	int s = sin(angle);
	int c = cos(angle);

	if ( v == 1 ) {
		MATRIX_MULT3x3 = 1<<12;
		MATRIX_MULT3x3 = 0;
		MATRIX_MULT3x3 = 0;

		MATRIX_MULT3x3 = 0;
		MATRIX_MULT3x3 = c;
		MATRIX_MULT3x3 = s;

		MATRIX_MULT3x3 = 0;
		MATRIX_MULT3x3 = -s;
		MATRIX_MULT3x3 = c;
	} else if ( v == 2 ) {
		MATRIX_MULT3x3 = c;
		MATRIX_MULT3x3 = 0;
		MATRIX_MULT3x3 = -s;

		MATRIX_MULT3x3 = 0;
		MATRIX_MULT3x3 = 1<<12;
		MATRIX_MULT3x3 = 0;

		MATRIX_MULT3x3 = s;
		MATRIX_MULT3x3 = 0;
		MATRIX_MULT3x3 = c;
	} else {
		MATRIX_MULT3x3 = c;
		MATRIX_MULT3x3 = s;
		MATRIX_MULT3x3 = 0;

		MATRIX_MULT3x3 = -s;
		MATRIX_MULT3x3 = c;
		MATRIX_MULT3x3 = 0;

		MATRIX_MULT3x3 = 0;
		MATRIX_MULT3x3 = 0;
		MATRIX_MULT3x3 = 1<<12;
	}
}

void arms(int t, int m)
{
	push();
//		translate(0.24f*m, 0.4f, 0);
		translate(983*m, 1638, 0);
//		rotateZ(30°*m);
		rotateZ(2145*m);
//		rotateX(cos(t)*20°+180°);
		rotateX(((cos(t)*1430)>>12)+12868);
//		translate(0, 0.3, 0);
		translate(0, 1229, 0);
		push();
//			scale(0.1, 0.3, 0.1);
			scale(410, 1229, 410);
			cube();
		pop();

//		translate(0, 0.22, 0);
		translate(0, 901, 0);
//		rotateY(abs(cos(t))*16*m);
		int act = cos(t)*1144;
		if ( act < 0 )
			act = -act;
		rotateY((act>>12)*m);
//		rotateX(100°);
		rotateX(7149);
//		rotateZ(165°*m);
		rotateZ(11796*m);
//		translate(0, 0.21, 0);
		translate(0, 860, 0);
		push();
//			scale(0.09, 0.27, 0.09);
			scale(369, 1106, 369);
			cube();
		pop();
	pop();
}

void legs(int t, int m)
{
	push();
//		translate(0.19*m, 0, -0.015);
		translate(778*m, 0, -61);
//		rotateX(cos(t)*13°-2.5);
		rotateX(((cos(t)*929)>>12)-228); // 929->1024 = -12 bytes !

//		translate(0, -0.7, 0);
		translate(0, -2867, 0);
		push();
//			scale(0.1, 0.25, 0.1);
			scale(410, 1024, 410);
			cube();
		pop();

//		float d = -min(0, cos(t+3.14157/2));
		int d = -cos(t+6434);
		if ( d < 0 )
			d = 0;
//		translate(0, d*0.15-0.52, d*0.015-0.06);
		translate(0, ((d*512)>>12)-2130, ((d*61)>>12)-246);
//		rotateX(10°);
		rotateX(715);
		push();
//			scale(0.1, 0.3, 0.1);
			scale(410, 1229, 410);
			cube();
		pop();

//		translate(0, -0.3, 0.1);
		translate(0, -1229, 410);
		push();
//			scale(0.1, 0.03, 0.2);
			scale(410, 123, 819);
			cube();
		pop();
	pop();
}

void robot(int t, int T)
{
#define robot_fall_speed 2048
#define robot_start 40
	t *= 402;

	// ast = |sin(t)|
	int ast = sin(t);
	if ( ast < 0 )
		ast = -ast;

	// act = |cos(t)|
	int act = cos(t);
	if ( act < 0 )
		act = -act;

	int fall;

	// head
	push();
//		translate(0, 0.71+0.05*abs(sin(t)), 0.04);
		fall = (robot_start+88)*robot_fall_speed - T*robot_fall_speed;
		if ( fall < 0 )
			fall = 0;
		translate(0, 2908+((ast*204)>>12)+fall, 164);
//		rotateX(-5°+10°*abs(cos(t)));
		rotateX((-357+715*act)>>12);
//		scale(0.2, 0.2, 0.2);
		scale(819, 819, 819);
		cube();
	pop();

	// body
	push();
//		translate(0, 0.05*abs(sin(t)), 0);
		fall = (robot_start+48)*robot_fall_speed - T*robot_fall_speed;
		if ( fall < 0 )
			fall = 0;
		translate(0, ((ast*204)>>12)+fall, 0);
//		rotateY(2.5°-5°*cos(t));
		rotateY(179-((357*cos(t))>>12));
//		scale(0.3, 0.5, 0.17);
		scale(1229, 2048, 696);
		cube();
	pop();

	// left side
	push();
	fall = (robot_start+56)*robot_fall_speed - T*robot_fall_speed;
	if ( fall < 0 )
		fall = 0;
	translate(0, fall, 0);
	arms(t, -1);
	pop();

	push();
	fall = (robot_start+8)*robot_fall_speed - T*robot_fall_speed;
	if ( fall < 0 )
		fall = 0;
	translate(0, fall, 0);
	legs(t, -1);
	pop();

	// right side
	t += 12868;
	push();
	fall = (robot_start+64)*robot_fall_speed - T*robot_fall_speed;
	if ( fall < 0 )
		fall = 0;
	translate(0, fall, 0);
	arms(t, 1);
	pop();

	push();
	fall = (robot_start+24)*robot_fall_speed - T*robot_fall_speed;
	if ( fall < 0 )
		fall = 0;
	translate(0, fall, 0);
	legs(t, 1);
	pop();
}

// r * cos((x*pi/2)/r) * cos((y*pi/2)/r) - r
// returns a fixed point altitude value in fx.6
int f(int x, int y)
{
	const int r = 32;
//	const int _r = (int)((0.5f/(float)r)*64.0f); // == 1 ...
//	x = (x*_r);
//	y = (y*_r);
	return ((r * (uber_cos(x) * uber_cos(y))>>18)) - (r<<6);
}

void sonic(int t)
{
	int i = 0;
	int y, x;

	rotateX(-1024);

	if ( t < 256 )
		t = 0;
	else
		t = -(t*2)&127;

	for ( y = -7*64+t ; y < 6*64+t ; y += 64 ) {
		for ( x = -7*64 ; x < 6*64 ; x += 64 ) {
			GFX_VERTEX10 = VERTEX(x,    f(x,    y),    y);
			GFX_VERTEX10 = VERTEX(x,    f(x,    y+64), y+64);
			GFX_VERTEX10 = VERTEX(x+64, f(x+64, y+64), y+64);
			GFX_VERTEX10 = VERTEX(x+64, f(x+64, y),    y);
			GFX_COLOR = (i&1) ? RGB15(29, 15, 4) : RGB15(4, 11, 28);
			i++;
		}
		//i++;
	}
}

void spot(int c1, int c2, int w, int h)
{
	GFX_BEGIN = QUAD;
	GFX_COLOR = c1;
	GFX_VERTEX10 = VERTEX(-64, h, 0);
	GFX_VERTEX10 = VERTEX( 64, h, 0);
	GFX_COLOR = c2;
	GFX_VERTEX10 = VERTEX( 64+w, 64, 0);
	GFX_VERTEX10 = VERTEX(-64-w, 64, 0);
}

void robot_solo(int t)
{
	int T = t;
	if ( t < 256 ) {
		// stopped for the intro
		t = 0;
	} else if ( t > 1152 ) {
		// tracted by the flying saucer
		int y;
		y = (t-1152)*58;
		if ( y > 22528 )
			y = 22528;
		translate(0, y, 0);
		y = (8*4096-y)/8;
		scale(y, y, y);
		t = 0;
	}
	robot(t, T);
}

int jump(int t)
{
	if ( t < 512 )
		return 0;
	t = t%64;
	t = t*8-384+128;
	t = 3072-t*t;
	if ( t < 0 )
		return 0;
	return t;
}

void robot_clone_wars(int t)
{
#define SPACE_FLOOR 1
#define FINAL_WALK_ON 1
#define LINES 6
#define SPACING 16384
	int i, j;

	//rotateX(2560);
	if ( (t & 1) == 0 ) { // different camera for different screens
		translate(5120, 44032, 20480);
		rotateZ(1792);
	} else {
		rotateX(2560);
	}

#if SPACE_FLOOR
	push();
	translate(0, -6144, -4096*4);
	rotateX(-12867/2);
	scale(4096*16, 4096*10, 4096*10);
	spot(RGB15(0, 7, 3), RGB15(0, 2, 1), 0, -64);
	pop();
#endif

#if SPACE_FLOOR
	int z = t*256-16384;
#else
	int z = t*256*8-16384*8;
#endif
	if ( z > 0 )
		z = 0;

	int lines = (t-192+8)/8;

	if ( lines < 2 )
		lines = 2;
	else if ( lines > LINES )
		lines = LINES;

	for ( i = 1 ; i < lines ; i++ ) {
		translate(0, 0, -8192);
		for ( j = 0 ; j < i ; j++ ) {
			if ( j == 2 && i == 5 )
				continue;
			push();
				translate(j * SPACING - ((i-1)*SPACING)/2, jump(t-i*4)+z, 0);
#if FINAL_WALK_ON
				if ( t < 512 )
					robot(8, 256);
				else
					robot(8+t-512, 256);
#else
				robot(8);
#endif
			pop();
		}
	}
}

void background(int t)
{
#if FADES
	if ( t == 1536 ) {
		fade_current = 0;
		fade_target = 16<<2;
	}
#endif
	if ( t < 1536 )
		spot(RGB15(31, 31, 31), RGB15(12, 12, 31), 0, -64);
	else
		spot(RGB15(1, 5, 2), RGB15(0, 0, 0), 0, -64);
}

void fs(int t)
{
	static int h[9] = { 64,		58,		51,		32,		26,		19,		10,		1,		0 };
	static int r[9] = { 0,		819,	1229,	1638,	3276,	4096,	3276,	2048,	0 };

	int y = 1024*32-t*32;
	if ( y < 0 )
		y = 0;
	translate(y, y, -y);

	GFX_COLOR = RGB15(15, 15, 15);
	int i, j;
	for ( i = 0 ; i < 8 ; i++ ) {
		for ( j = 0 ; j < 8192 ; j += 512 ) {
			GFX_NORMAL = VERTEX((uber_cos(j) * r[i])>>18, h[i], (uber_sin(j) * r[i])>>18);
			GFX_VERTEX10 = VERTEX((uber_cos(j) * r[i])>>18, h[i], (uber_sin(j) * r[i])>>18);
			GFX_VERTEX10 = VERTEX((uber_cos(j+512) * r[i])>>18, h[i], (uber_sin(j+512) * r[i])>>18);
			GFX_VERTEX10 = VERTEX((uber_cos(j+512) * r[i+1])>>18, h[i+1], (uber_sin(j+512) * r[i+1])>>18);
			GFX_VERTEX10 = VERTEX((uber_cos(j) * r[i+1])>>18, h[i+1], (uber_sin(j) * r[i+1])>>18);
		}
	}
}

void fs_beam(int t)
{
	int h = 64+8+384-t*4;
	if ( h < 0 )
		h = 0;
	GFX_POLY_FORMAT = LIGHT0|POLYFRONT|ALPHA(15);
	spot(RGB15(0, 31, 4), RGB15(0, 31, 4), -32, h-384);
}

typedef struct {
	void (*draw)(int time);
	s16 start, end;
	s8 ty, tz;
	s8 s;
} Drawable;

Drawable demo[] =
{
	// draw					start, 	end		ty, tz		scale
	{ robot_solo, 			0, 		1536,	 1, -15, 	4 	},
	{ sonic, 				0, 		1536, 	-8, -24, 	4 	},
	{ fs, 					0, 		1536, 	21, -15, 	4 	},
	{ robot_clone_wars, 	1536, 	2576,	-4, -16, 	2 	},
	{ background, 			0, 		2576, 	 9, -44, 	32 	},
	{ fs_beam, 				1024, 	1536, 	18, -13, 	4 	},
};

void Main()
{
	extern void Init();
	Init();
	init();

	// Init sprites to display like a big bitmap background
	//VRAM_D_CR = VRAM_D_SUB_SPRITE | VRAM_ENABLE;
	int y, x;
	u16 * ptr = OAM_SUB;
	for ( y = 0 ; y < 3 ; y++ ) {
		for ( x = 0 ; x < 4 ; x++ ) {
			// attribute 0
			*ptr++ = ATTR0_BMP | (y*64);
			// attribute 1
			*ptr++ = ATTR1_SIZE_64 | (x*64);
			// attribute 2
			*ptr++ = ATTR2_ALPHA(15) | (x*8+y*256);
			// pad (matrix)
			ptr++;
		}
	}
	
	int t = 0;

	while ( t < 2576 ) {
#if FADES
		if ( fade_current < fade_target )
			fade_current++;
		else if ( fade_current > fade_target )
			fade_current--;

		int v = 0;
		if ( fade_current < (16 << 2) )
			v = DARK | (16 - (fade_current >> 2));
		else if ( fade_current > (16 << 2) )
			v = BRIGHT | ((fade_current >> 2) - 16);

		REG_MASTER_BRIGHT = v;
		REG_MASTER_BRIGHT_SUB = v;
#endif

		identity();

		// Dual screen 3D
		if ( t&1 ) {
			REG_POWERCNT &= ~POWER_SWAP_LCDS; // main on bottom
			VRAM_C_CR = VRAM_ENABLE;
			VRAM_D_CR = VRAM_D_SUB_SPRITE | VRAM_ENABLE;
			REG_DISPCAPCNT = DCAP_BANK(2) | DCAP_ENABLE | DCAP_SIZE(3);
		} else {
			REG_POWERCNT |= POWER_SWAP_LCDS; // main on top
			VRAM_C_CR = VRAM_C_SUB_BG | VRAM_ENABLE;
			VRAM_D_CR = VRAM_ENABLE;
			REG_DISPCAPCNT = DCAP_BANK(3) | DCAP_ENABLE | DCAP_SIZE(3);
			translate(0, -5*4096, 0);
		}

		// Reset polygon attributes
		GFX_POLY_FORMAT = LIGHT0|POLYFRONT|SOLID;

		// Lightweight 3D player -olol
		int i;
		for ( i = 0 ; i < sizeof(demo)/sizeof(Drawable) ; i++ ) {
			if ( t >= demo[i].start && t < demo[i].end ) {
				push();
					translate(0, demo[i].ty*1024, demo[i].tz*1024);
					scale(demo[i].s*1024, demo[i].s*1024, demo[i].s*1024);
					demo[i].draw(t-demo[i].start);
				pop();
			}
		}

		t++;
		swap();
	}

	extern void seeya();
	seeya();
}
