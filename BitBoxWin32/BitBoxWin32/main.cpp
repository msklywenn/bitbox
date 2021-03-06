#include <SDL.h>
#include <windows.h>
#include <GL/gl.h>
#include "trig.h"
#include "glext.h"

#include "tune.h"
#include "synth.h"

#ifdef _WINDOWS
#include <windows.h>
#endif

#define WIDTH 800
#define HEIGHT 600

Uint32 timer(Uint32 interval, void * param)
{
	Synth * synth = (Synth *) param;

	static int lastRow = -42;
	int currentRow = synth->getCurrentRow();
	if ( currentRow != lastRow ) {
		lastRow = currentRow;
	}

	// Detect end of song and stop synth
	int end = 0;
	for ( int i = 0 ; i < 8 ; i++ )
		if ( currentRow > synth->getTune()->channels[i].lastRow 
				&& synth->getVolume(i) == 0 )
			end++;
		else
			break;
	if ( end == 8 )
		synth->stop(false);

	return interval;
}

PFNGLCREATESHADERPROC glCreateShader = 0;
PFNGLCREATEPROGRAMPROC glCreateProgram = 0;
PFNGLLINKPROGRAMPROC glLinkProgram = 0;
PFNGLUSEPROGRAMPROC glUseProgram = 0;
PFNGLDETACHSHADERPROC glDetachShader = 0;
PFNGLATTACHSHADERPROC glAttachShader = 0;
PFNGLDELETEPROGRAMPROC glDeleteProgram = 0;
PFNGLDELETESHADERPROC glDeleteShader = 0;
PFNGLSHADERSOURCEPROC glShaderSource = 0;
PFNGLCOMPILESHADERPROC glCompileShader = 0;
GLuint fsh;
const GLchar* fshSource = "void main()\
{\
	ivec3 i = ivec3(gl_Color * 63.0);\
	gl_FragColor = vec4(ivec3(vec3(i/63.0) * 31.0) / 31.0, 1.0);\
}";
GLuint program;

void InitVideo()
{	
	glClearColor(0, 0, 0, 1.0f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	
	//glEnable(GL_POLYGON_SMOOTH);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT, GL_FILL);
	glCullFace(GL_BACK);
	
	glMatrixMode(GL_PROJECTION);
	float matrix[4*4] =
	{
		6587/4096.0f, 	0, 	0,	0,
		0, 	8783/4096.0f, 	0,	0,
		0, 	0, 	-4116/4096.0f,	-4096/4096.0f,
		0, 	0, 	-821/4096.0f,	0,
	};
	glLoadMatrixf(matrix);
	glMatrixMode(GL_MODELVIEW);

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	static float diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	static float position[] = { 2.0f, 4.0f, 2.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glCreateShader = (PFNGLCREATESHADERPROC) wglGetProcAddress("glCreateShader");
	glCreateProgram = (PFNGLCREATEPROGRAMPROC) wglGetProcAddress("glCreateProgram");
	glLinkProgram = (PFNGLLINKPROGRAMPROC) wglGetProcAddress("glLinkProgram");
	glUseProgram = (PFNGLUSEPROGRAMPROC) wglGetProcAddress("glUseProgram");
	glDetachShader = (PFNGLDETACHSHADERPROC) wglGetProcAddress("glDetachShader");
	glAttachShader = (PFNGLATTACHSHADERPROC) wglGetProcAddress("glAttachShader");
	glDeleteProgram = (PFNGLDELETEPROGRAMPROC) wglGetProcAddress("glDeleteProgram");
	glDeleteShader = (PFNGLDELETESHADERPROC) wglGetProcAddress("glDeleteShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC) wglGetProcAddress("glShaderSource");
	glCompileShader = (PFNGLCOMPILESHADERPROC) wglGetProcAddress("glCompileShader");

	fsh = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsh, 1, & fshSource, 0);
	glCompileShader(fsh);
	program = glCreateProgram();
	glAttachShader(program, fsh);
	glLinkProgram(program);
}

int fade_current = 31 << 2; // starts white
int fade_target = 16 << 2;

void cube()
{
	glUseProgram(program);

	glDisable(GL_BLEND);
	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f,  1.0f);
		glVertex3f( 1.0f, -1.0f,  1.0f);
		glVertex3f( 1.0f,  1.0f,  1.0f);
		glVertex3f(-1.0f,  1.0f,  1.0f);

		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f,  1.0f, -1.0f);
		glVertex3f( 1.0f,  1.0f, -1.0f);
		glVertex3f( 1.0f, -1.0f, -1.0f);

		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f( 1.0f, -1.0f, -1.0f);
		glVertex3f( 1.0f, -1.0f,  1.0f);
		glVertex3f(-1.0f, -1.0f,  1.0f);

		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f,  1.0f, -1.0f);
		glVertex3f(-1.0f,  1.0f,  1.0f);
		glVertex3f( 1.0f,  1.0f,  1.0f);
		glVertex3f( 1.0f,  1.0f, -1.0f);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f,  1.0f);
		glVertex3f(-1.0f,  1.0f,  1.0f);
		glVertex3f(-1.0f,  1.0f, -1.0f);

		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f( 1.0f, -1.0f, -1.0f);
		glVertex3f( 1.0f,  1.0f, -1.0f);
		glVertex3f( 1.0f,  1.0f,  1.0f);
		glVertex3f( 1.0f, -1.0f,  1.0f);
	glEnd();

	glUseProgram(0);
}

#define RGB15(r, g, b) ((r)|((g)<<5)|((b)<<10))
#define RED(rgb) ( rgb & 0x1F )
#define GREEN(rgb) ((rgb>>5)&0x1F)
#define BLUE(rgb) ((rgb>>10)&0x1F)

#define identity glLoadIdentity
#define push glPushMatrix
#define pop glPopMatrix
#define translate(x, y, z) glTranslatef((x) / 4096.0f, (y) / 4096.0f, (z) / 4096.0f)
#define scale(x, y, z) glScalef((x) / 4096.0f, (y) / 4096.0f, (z) / 4096.0f)

#define rotateX(a) rotate(a, 0)
#define rotateY(a) rotate(a, 1)
#define rotateZ(a) rotate(a, 2)

void rotate(int a, int v)
{
	float angle = a / 12867.0f * 180.0f;
	
	if ( v == 1 )
		glRotatef(angle, 0, 1, 0);
	else if ( v == 2 )
		glRotatef(angle, 0, 0, 1);
	else
		glRotatef(angle, 1, 0, 0);
}

int uber_sin(int x)
{
	int ax;
	x = 4096 - (x & 0x1FFF);
	ax = x;
	if ( ax < 0 )
		ax = -ax;
	return 4 * x - ((4 * x * ax) >> 12);
}

void arms(int t, int m)
{
	push();
//		translate(0.24f*m, 0.4f, 0);
		translate(983*m, 1638, 0);
//		rotateZ(30�*m);
		rotateZ(2145*m);
//		rotateX(cos(t)*20�+180�);
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
//		rotateX(100�);
		rotateX(7149);
//		rotateZ(165�*m);
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
		translate(778*m, 0, -61);
		rotateX(((cos(t)*929)>>12)-228); // 929->1024 = -12 bytes !

		translate(0, -2867, 0);
		push();
			scale(410, 1024, 410);
			cube();
		pop();

		int d = -cos(t+6434);
		if ( d < 0 )
			d = 0;
		translate(0, ((d*512)>>12)-2130, ((d*61)>>12)-246);
		rotateX(715);
		push();
			scale(410, 1229, 410);
			cube();
		pop();

		translate(0, -1229, 410);
		push();
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
//		rotateX(-5�+10�*abs(cos(t)));
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
//		rotateY(2.5�-5�*cos(t));
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

	glBegin(GL_QUADS);
	for ( y = -7*64+t ; y < 6*64+t ; y += 64 ) {
		for ( x = -7*64 ; x < 6*64 ; x += 64 ) {
			if ( i & 1 )
				glColor3f(29/31.0f, 15/31.0f, 4/31.0f);
			else
				glColor3f(4/31.0f, 11/31.0f, 28/31.0f);
			glVertex3f(x / 64.0f, f(x, y)/64.0f, y / 64.0f);
			glVertex3f(x / 64.0f, f(x, y+64)/64.0f, y / 64.0f + 1.0f);
			glVertex3f(x / 64.0f + 1.0f, f(x+64, y+64)/64.0f, y / 64.0f + 1.0f);
			glVertex3f(x / 64.0f + 1.0f, f(x+64, y)/64.0f, y / 64.0f);
			i++;
		}
	}
	glEnd();
}

void spot(int c1, int c2, int w, int h)
{
	float c1r = RED(c1)/31.0f, c1g = GREEN(c1)/31.0f, c1b = BLUE(c1)/31.0f;
	float c2r = RED(c2)/31.0f, c2g = GREEN(c2)/31.0f, c2b = BLUE(c2)/31.0f;
	glBegin(GL_QUADS);
		glColor3f(c1r, c1g, c1b);
		glVertex3f(-1.0f, h/64.0f, 0.0f);
		glVertex3f(1.0f, h/64.0f, 0.0f);
		glColor3f(c2r, c2g, c2b);
		glVertex3f(1.0f + w / 64.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f-w/64.0f, 1.0f, 0.0f);
	glEnd();
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

	push();
		translate(0, -6144, -4096*4);
		rotateX(-12867/2);
		scale(4096*16, 4096*10, 4096*10);
		spot(RGB15(0, 7, 3), RGB15(0, 2, 1), 0, -64);
	pop();

	int z = t*256-16384;
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
				if ( t < 512 )
					robot(8, 256);
				else
					robot(8+t-512, 256);
			pop();
		}
	}
}

void background(int t)
{
	glDisable(GL_BLEND);
	if ( t == 1536 ) {
		fade_current = 0;
		fade_target = 16<<2;
	}
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

	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	int i, j;
	glBegin(GL_QUADS);
	glColor3f(0.5f, 0.5f, 0.5f);
	for ( i = 0 ; i < 8 ; i++ ) {
		for ( j = 0 ; j < 8192 ; j += 512 ) {
			glNormal3f(((uber_cos(j) * r[i])>>18) / 64.0f, h[i]/64.0f, ((uber_sin(j) * r[i])>>18)/64.0f);
			glVertex3f(((uber_cos(j) * r[i])>>18) / 64.0f, h[i]/64.0f, ((uber_sin(j) * r[i])>>18)/64.0f);
			glVertex3f(((uber_cos(j+512) * r[i])>>18) / 64.0f, h[i]/64.0f, ((uber_sin(j+512) * r[i])>>18)/64.0f);
			glVertex3f(((uber_cos(j+512) * r[i+1])>>18) / 64.0f, h[i+1]/64.0f, ((uber_sin(j+512) * r[i+1])>>18)/64.0f);
			glVertex3f(((uber_cos(j) * r[i+1])>>18) / 64.0f, h[i+1]/64.0f, ((uber_sin(j) * r[i+1])>>18)/64.0f);
		}
	}
	glEnd();
	glEnable(GL_CULL_FACE);
}

void fs_beam(int t)
{
	int h = 64+8+384-t*4;
	if ( h < 0 )
		h = 0;
	//GFX_POLY_FORMAT = LIGHT0|POLYFRONT|ALPHA(15);
	glEnable(GL_BLEND);
	spot(RGB15(0, 31, 4), RGB15(0, 31, 4), -32, h-384);
}

typedef short s16;
typedef char s8;

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

int mouseX, mouseY;

void Render(int t)
{
	if ( t < 2576 ) {
		if ( fade_current < fade_target )
			fade_current++;
		else if ( fade_current > fade_target )
			fade_current--;

		//int v = 0;
		//if ( fade_current < (16 << 2) )
		//	v = DARK | (16 - (fade_current >> 2));
		//else if ( fade_current > (16 << 2) )
		//	v = BRIGHT | ((fade_current >> 2) - 16);

		//REG_MASTER_BRIGHT = v;
		//REG_MASTER_BRIGHT_SUB = v;

		identity();

		// Dual screen 3D
		if ( t&1 ) {
			glViewport(WIDTH/2 - 256/2, HEIGHT/2 - 384/2 - 96/2, 255, 191);
		} else {
			translate(0, -5*4096, 0);
			glViewport(WIDTH/2 - 256/2, HEIGHT/2 - 384/2 + 192 - 96/2 + 96, 255, 191);
		}

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
	}
}

int main(int argc, char ** argv)
{
	SDL_Event event;
	bool running = true;
	
	int t = 0;

#ifdef _WINDOWS
#ifdef _DEBUG
	AllocConsole();
//	freopen("CONOUT$", "wb", stderr);
//	freopen("CONOUT$", "wb", stdout);
#endif	
#endif

	SDL_Init(SDL_INIT_EVERYTHING);

	Tune * tune = new Tune();
	Synth * synth = new Synth(tune);
	if ( ! SDL_AddTimer(100, timer, synth) )
		return 42;

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 1);
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 2);
	SDL_Surface * screen = SDL_SetVideoMode(WIDTH, HEIGHT, 16, SDL_DOUBLEBUF|SDL_HWSURFACE|SDL_OPENGL);
	SDL_WM_SetCaption("BitBox - Winport", "BitBox - Winport");
	InitVideo();

	synth->play();	
	tune->Load("plop");

	Uint32 start = SDL_GetTicks();

	while ( running ) {
		while ( SDL_PollEvent(& event) )
		{
			switch ( event.type ) {
				case SDL_MOUSEMOTION:
					mouseX = event.motion.x;
					mouseY = event.motion.y;
					break;
				case SDL_QUIT:
					running = false;
					break;
				case SDL_VIDEORESIZE:
				case SDL_VIDEOEXPOSE:
					break;
				case SDL_KEYDOWN:
					if ( event.key.keysym.sym == SDLK_ESCAPE ) // Quit...
						running = false;
					break;
				default:
					break;
			}
		}

		Uint32 now = SDL_GetTicks();

		t = (now - start) / 16;

		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

		Render(t);
		Render(t+1);
	
		SDL_GL_SwapBuffers();
	}

	delete synth;
	delete tune;

	SDL_FreeSurface(screen);
	SDL_Quit();

#ifdef __WIN32__
#ifdef _DEBUG
	FreeConsole();
#endif
#endif

	return 0;
}
