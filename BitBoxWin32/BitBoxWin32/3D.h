#ifndef _3D_H_
#define _3D_H_

#include <nds.h>

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
#define ALPHA(a) ((a)<<16)
#define WIREFRAME (0<<16)

// GX FIFO command packer
#define COMMAND(a,b,c,d) \
	(((a)&0xFF)|(((b)&0xFF)<<8)|(((c)&0xFF)<<16)|(((d)&0xFF)<<24))

void call_list(u32 * list, int size);

#define push() MATRIX_PUSH = 0
#define pop() MATRIX_POP = 1
#define identity() MATRIX_IDENTITY = 0
#define swap() GFX_FLUSH = 0
#define translate(x, y, z) \
	MATRIX_TRANSLATE = x; \
	MATRIX_TRANSLATE = y; \
	MATRIX_TRANSLATE = z
#define scale(x, y, z) \
	MATRIX_SCALE = x; \
	MATRIX_SCALE = y; \
	MATRIX_SCALE = z

void rotate(int angle, int v);

#define rotateX(angle) rotate(angle, 1)
#define rotateY(angle) rotate(angle, 2)
#define rotateZ(angle) rotate(angle, 3)

#endif // _3D_H_
