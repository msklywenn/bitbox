#include <nds.h>

#include "options.h"

// Commands
#define CMTXMODE 		0x10
#define CMTXPUSH 		0x11
#define CMTXPOP			0x12
#define CMTXIDENTITY 	0x15
#define CMTXLOAD4x4 	0x16
#define CMTXLOAD4x3 	0x17
#define CMTXMULT3x3 	0x1A
#define CMTXSCALE 		0x1B
#define CMTXTRANSLATE 	0x1C
#define CCOLOR			0x20
#define CNORMAL 		0x21
#define CVERTEX 		0x24
#define CPOLYATTR 		0x29
#define CDIFAMB 		0x30
#define CLIGHTVECTOR	0x32
#define CLIGHTCOLOR 	0x33
#define CBEGIN			0x40
#define CVIEWPORT 		0x60

// Parameters
#define PROJECTION 	0
#define MODELVIEW 	2

#define QUAD 1

#define NORMAL(x,y,z) (((x)&0x3FF)|(((y)&0x3FF)<<10)|(((z)&0x3FF)<<20)) 
#define VERTEX(x,y,z) \
	(((x)&0x3FF)|(((y)&0x3FF)<<10)|(((z)&0x3FF)<<20))

#define DIFAMB(dif,amb) ((dif)|((amb)<<16))

#define VIEWPORT(x1,y1,x2,y2) ((x1)|((y1)<<8)|((x2)<<16)|((y2)<<24))

// Polygon attributes
#define LIGHT0 BIT(0)
#define POLYFRONT BIT(7)
#define POLYBACK BIT(6)
#define SOLID (31<<16)
#define WIREFRAME (0<<16)

// FIFO command packer
#define COMMAND(a,b,c,d) \
	(((a)&0xFF)|(((b)&0xFF)<<8)|(((c)&0xFF)<<16)|(((d)&0xFF)<<24))


int uber_sin(int x)
{
	x = 4096 - (x & 0x1FFF);
	int ax = x;
	if ( ax < 0 )
		ax = -ax;
	return 4 * x - ((4 * x * ax) >> 12);
}

#define uber_cos(x) uber_sin(x + 0x800)


#undef B
#undef C

void callList(u32 * list, int size)
{
	DMA_SRC(0) = (unsigned int) list;
	DMA_DEST(0) = 0x4000400; //GXFIFO
	DMA_CR(0) = DMA_FIFO | size;
	while ( DMA_CR(0) & DMA_BUSY )
		;
}

u32 bglist[] =
{
	COMMAND(CCOLOR, CVERTEX, CVERTEX, CCOLOR),
	RGB15(31, 31, 31),
	VERTEX(-4*64, -4*64, 0),
	VERTEX( 4*64, -4*64, 0),
	RGB15(12, 12, 31),
	COMMAND(CVERTEX, CVERTEX, 0, 0),
	VERTEX( 4*64,  4*64, 0),
	VERTEX(-4*64,  4*64, 0),
};
#define bg() callList(bglist, sizeof(bglist)/sizeof(u32))

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
#define cube() callList(cubelist, sizeof(cubelist)/sizeof(u32))

u32 initlist[] =
{
	COMMAND(CVIEWPORT, CMTXMODE, CMTXLOAD4x4, CMTXMODE),
	VIEWPORT(0, 0, 255, 191),
	PROJECTION,
	// Projection matrix Perspective(fov=50°, near=0.1, far=40, ratio=1.33)
	6587, 	0, 	0,	0,
	0, 	8783, 	0,	0,
	0, 	0, 	-4116,	-4096,
	0, 	0, 	-821,	0,
	MODELVIEW,

	COMMAND(CPOLYATTR, CMTXIDENTITY, CLIGHTVECTOR, CLIGHTCOLOR),
	LIGHT0|POLYFRONT|SOLID,
	NORMAL(-96, -144, -482),
	RGB15(31, 31, 31),
};
#define init() callList(initlist, sizeof(initlist)/sizeof(u32))

int abs(int x)
{
	return ( x < 0 ) ? -x : x;
}

int min(int a, int b)
{
	return ( a < b ) ? a : b;
}

// input : fixed .12
// output : fixed .12
int sin(int x)
{
	// translate x into [-pi, pi].f12
	while ( x > 12868 )
		x -= 25736;
	while ( x < -12868 )
		x += 25736;
	// compute sin(x)
	// see http://www.devmaster.net/forums/showthread.php?t=5784
	const int B = 5215;
	const int C = -1660;
	return (B*x + ((C*x)>>12)*abs(x))>>12;
}

int cos(int x)
{
	x += 6434;
	return sin(x);
}

inline void push()
{
	MATRIX_PUSH = 0;
}

inline void pop()
{
	MATRIX_POP = 1;
}

inline void identity()
{
	MATRIX_IDENTITY = 0;
}

inline void translate(int x, int y, int z)
{
	MATRIX_TRANSLATE = x;
	MATRIX_TRANSLATE = y;
	MATRIX_TRANSLATE = z;
}

inline void scale(int x, int y, int z)
{
	MATRIX_SCALE = x;
	MATRIX_SCALE = y;
	MATRIX_SCALE = z;
}

void rotate(int angle, int x, int y, int z)
{
	int s = sin(angle);
	int c = cos(angle);

	MATRIX_MULT3x3 = (x == 0) ? c : 1<<12;
	MATRIX_MULT3x3 = z * s;
	MATRIX_MULT3x3 = y * -s;

	MATRIX_MULT3x3 = z * -s;
	MATRIX_MULT3x3 = (y == 0) ? c : 1<<12;
	MATRIX_MULT3x3 = x * s;

	MATRIX_MULT3x3 = y * s;
	MATRIX_MULT3x3 = x * -s;
	MATRIX_MULT3x3 = (z == 0) ? c : 1<<12;
}

void uber_rotate(int angle, int x, int y, int z)
{
	int s = uber_sin(angle);
	int c = uber_cos(angle);

	MATRIX_MULT3x3 = (x == 0) ? c : 1<<12;
	MATRIX_MULT3x3 = z * s;
	MATRIX_MULT3x3 = y * -s;

	MATRIX_MULT3x3 = z * -s;
	MATRIX_MULT3x3 = (y == 0) ? c : 1<<12;
	MATRIX_MULT3x3 = x * s;

	MATRIX_MULT3x3 = y * s;
	MATRIX_MULT3x3 = x * -s;
	MATRIX_MULT3x3 = (z == 0) ? c : 1<<12;
}

#define rotateX(angle) rotate(angle, 1, 0, 0)
#define rotateY(angle) rotate(angle, 0, 1, 0)
#define rotateZ(angle) rotate(angle, 0, 0, 1)
#define uber_rotateX(angle) uber_rotate(angle, 1, 0, 0)
#define uber_rotateY(angle) uber_rotate(angle, 0, 1, 0)
#define uber_rotateZ(angle) uber_rotate(angle, 0, 0, 1)

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
		rotateY((abs(cos(t)*1144)>>12)*m);
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
		rotateX(((cos(t)*929)>>12)-228);

//		translate(0, -0.7, 0);
		translate(0, -2867, 0);
		push();
//			scale(0.1, 0.25, 0.1);
			scale(410, 1024, 410);
			cube();
		pop();

//		float d = -min(0, cos(t+3.14157/2));
		int d = -min(0, cos(t+6434));
//		translate(0, d*0.15-0.52, d*0.015-0.06);
		translate(0, ((d*614)>>12)-2130, ((d*61)>>12)-246);
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

void robot(int t)
{
	// head
	push();
//		translate(0, 0.71+0.05*abs(sin(t)), 0.04);
		translate(0, 2908+((abs(sin(t))*204)>>12), 164);
//		rotateX(-5°+10°*abs(cos(t)));
		rotateX((-357+715*abs(cos(t)))>>12);
//		scale(0.2, 0.2, 0.2);
		scale(819, 819, 819);
		cube();
	pop();

	// body
	push();
//		translate(0, 0.05*abs(sin(t)), 0);
		translate(0, (abs(sin(t))*204)>>12, 0);
//		rotateY(2.5°-5°*cos(t));
		rotateY(179-((357*cos(t))>>12));
//		scale(0.3, 0.5, 0.17);
		scale(1229, 2048, 696);
		cube();
	pop();

	// left side
	arms(t, -1);
	legs(t, -1);

	// right side
	t += 12868;
	arms(t, 1);
	legs(t, 1);
}

// r * cos((x*pi/2)/r) * cos((y*pi/2)/r) - r
int f(int x, int y)
{
	const int r = 25;
	return (r * (uber_cos(x) * uber_cos(y))>>18) - (r<<6);
}

void sonic(int t)
{
	int i = 0;
	int y, x;

	const u16 colors[2] = { RGB15(29, 15, 4), RGB15(4, 11, 28) };

	for ( y = -7*64+t ; y < 6*64+t ; y += 64 ) {
		for ( x = -7*64 ; x < 6*64 ; x += 64 ) {
			GFX_VERTEX10 = VERTEX(x,    f(x,    y),    y);
			GFX_VERTEX10 = VERTEX(x,    f(x,    y+64), y+64);
			GFX_VERTEX10 = VERTEX(x+64, f(x+64, y+64), y+64);
			GFX_VERTEX10 = VERTEX(x+64, f(x+64, y),    y);
			// -4B by putting next two lines at the end of this loop
			GFX_COLOR = colors[i&1];
			i++;
		}
		//i++;
	}
}

#if STDLIB
int main()
#else
void Main()
#endif
{	
	int t = 0;

#if CAMERA
	int rX = 0, rrX = 0;
	int rY = 0, rrY = 0;
	int tX = 0;
	int tY = 0;
	int tZ = 0;

	touchPosition start;
	touchPosition now;
#endif
	
	// initialize 3D
	REG_POWERCNT = POWER_ALL;
#if SAFE
	while ( GFX_STATUS & BIT(27) )
		;
	GFX_STATUS |= BIT(29); // clear fifo
	GFX_FLUSH = 0;
	GFX_CONTROL = 0;
#endif
	GFX_CLEAR_DEPTH = 0x7FFF;

	GFX_CONTROL = GL_ANTIALIAS;
	GFX_CLEAR_COLOR = 0x3F1F0000; // black, alpha=31, id=63

	init();

	// Initialize 2D Engines
	REG_DISPCNT = MODE_0_2D
		| DISPLAY_BG0_ACTIVE
		| ENABLE_3D;
	REG_DISPCNT_SUB = MODE_5_2D
		| DISPLAY_BG3_ACTIVE
		| DISPLAY_SPR_ACTIVE
		| DISPLAY_SPR_2D
		| DISPLAY_SPR_2D_BMP_256;

	// Init SUB BG0
	//VRAM_C_CR = VRAM_C_SUB_BG | VRAM_ENABLE;
	REG_BG3CNT_SUB = BG_BMP16_256x256;
	REG_BG3PA_SUB = 1<<8;
#if SAFE
	REG_BG3PB_SUB = 0;
	REG_BG3PC_SUB = 0;
#endif
	REG_BG3PD_SUB = 1<<8;

	// Init sprites to display like a big bitmap background
	//VRAM_D_CR = VRAM_D_SUB_SPRITE | VRAM_ENABLE;
	int y, x;
	u16 * ptr = OAM_SUB;
	for ( y = 0 ; y < 3 ; y++ ) {
		for ( x = 0 ; x < 4 ; x++ ) {
			// attribute 0
			*ptr++ = ATTR0_BMP | (y*64); // attr0
			// attribute 1
			*ptr++ = ATTR1_SIZE_64 | (x*64); // attr1
			// attribute 2
			*ptr++ = ATTR2_ALPHA(15) | (x*8+y*256);
			// pad/matrix
			*ptr++;
		}
	}
	
	while ( 1 ) {
		identity();
		if ( t&1 ) {
			REG_POWERCNT &= ~POWER_SWAP_LCDS; // main on bottom
			VRAM_C_CR = VRAM_ENABLE;
			VRAM_D_CR = VRAM_D_SUB_SPRITE | VRAM_ENABLE;
			REG_DISPCAPCNT = DCAP_BANK(2) | DCAP_ENABLE | DCAP_SIZE(3);
			//rotateX(-t+512);
		} else {
			REG_POWERCNT |= POWER_SWAP_LCDS; // main on top
			VRAM_C_CR = VRAM_C_SUB_BG | VRAM_ENABLE;
			VRAM_D_CR = VRAM_ENABLE;
			REG_DISPCAPCNT = DCAP_BANK(3) | DCAP_ENABLE | DCAP_SIZE(3);
			rotateZ(8192);
			rotateX(6144);
			translate(0, -4*4096, 9216);
		}

#if 0
#if CAMERA
		rotateX((rX+rrX) * DEGREES_IN_CIRCLE / 360.0);
		rotateY((rY+rrY) * DEGREES_IN_CIRCLE / 360.0);
		translate(tX, tZ, tY);
#endif
#endif
		translate(0, 1024, -4096);

		push();
			translate(0, 128, -11059);
			rotateX(-512);
			scale(0, 0, 0);
			robot(t*402);
		pop();

		push();
			translate(0, 0, -40960);
			scale(20480, 8192, 4096);
			bg();
		pop();

		push();
			translate(0, -9216, -20480);
			uber_rotateX((rX+rrX)*16);
			sonic(-(t*2)&127);
		pop();
		
		GFX_FLUSH = 0;
		t++;

#if CAMERA
		scanKeys();

		// look around
		u16 keys = keysDown();
		if ( keys & KEY_TOUCH )
			touchRead(& start);

		keys = keysUp();
		if ( keys & KEY_TOUCH ) {
			rX = rX + rrX;
			rY = rY + rrY;
			rrX = 0;
			rrY = 0;
		}

		keys = keysHeld();
		if ( keys & KEY_TOUCH ) {
			touchRead(& now);
			rrX = now.py - start.py;
			rrY = now.px - start.px;
		}

		// world move
		if ( keys & KEY_UP ) tY += 128;
		if ( keys & KEY_DOWN ) tY -= 128;
		if ( keys & KEY_LEFT ) tX += 128;
		if ( keys & KEY_RIGHT ) tX -= 128;
		if ( keys & KEY_L ) tZ += 128;
		if ( keys & KEY_R ) tZ -= 128;

		// reset
		if ( keys & KEY_SELECT ) { rX = rY = tX = tY = tZ = 0; }
#endif
	}

#if STDLIB
	return 0;
#endif
}
