// Commands
#define CBEGIN 0x40
#define CCOLOR 0x20
#define CVERTEX 0x24
#define CNORMAL 0x21

// Parameters
#define QUAD 0x1
#define QUADSTRIP 0x3
#define GRAY RGB15(15, 15, 15)
#define NORMAL(x,y,z) () // (1bit sign + 9bit fractional part)
#define VERTEX(x,y,z) () // (signed, with 6bit fractional part)

#define COMMAND(a,b,c,d) \
	((a)&0xFF|(((b)&0xFF)<<8)|(((c)&0xFF)<<16)|(((d)&0xFF)<<24))

u32 cubelist[] =
{
	COMMAND(CBEGIN, CCOLOR, CNORMAL, CVERTEX),
	QUADSTRIP,
	GRAY,
	NORMAL( 0,-1, 0),
	VERTEX(-1,-1,-1),
	COMMAND(CVERTEX, CVERTEX, CVERTEX, CNORMAL),
	VERTEX( 1,-1,-1),
	VERTEX(-1,-1, 1),
	VERTEX( 1,-1, 1),
	NORMAL( 0, 0, 1),
	COMMAND(CVERTEX, CVERTEX, CNORMAL, CVERTEX),
	VERTEX(-1, 1, 1),
	VERTEX( 1, 1, 1),
	NORMAL( 0, 1, 0),
	VERTEX(-1, 1,-1),
	COMMAND(CVERTEX, CNORMAL, CVERTEX, CVERTEX),
	VERTEX( 1, 1,-1),
	NORMAL( 0, 0,-1),
	VERTEX(-1,-1,-1),
	VERTEX( 1,-1,-1),
	COMMAND(CBEGIN, CNORMAL, CVERTEX, CVERTEX),
	QUAD,
	NORMAL( 1, 0, 0),
	VERTEX( 1,-1,-1),
	VERTEX( 1,-1, 1),
	COMMAND(CVERTEX, CVERTEX, CNORMAL, CVERTEX),
	VERTEX( 1, 1, 1),
	VERTEX( 1, 1,-1),
	NORMAL(-1, 0, 0),
	VERTEX(-1,-1,-1),
	COMMAND(CVERTEX, CVERTEX, CVERTEX, 0),
	VERTEX(-1,-1, 1),
	VERTEX(-1, 1, 1),
	VERTEX(-1, 1,-1),
};

inline void cube()
{
	extern u32 cubelist[];

	DMA_SRC(0) = cubelist;
	DMA_DEST(0) = 0x4000400;
	DMA_CR(0) = DMA_FIFO | (sizeof(cubelist)/sizeof(u32));
	while ( DMA_CR(0) & DMA_BUSY )
		;
}
