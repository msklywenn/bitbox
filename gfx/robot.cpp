#include <SDL.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#define _USE_MATH_DEFINES
#include <math.h>

#define WIDTH 640
#define HEIGHT 480

inline void glRotateX(float angle) { glRotatef(angle, 1.0f, 0.0f, 0.0f); }
inline void glRotateY(float angle) { glRotatef(angle, 0.0f, 1.0f, 0.0f); }
inline void glRotateZ(float angle) { glRotatef(angle, 0.0f, 0.0f, 1.0f); }

void cube()
{
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
}

float param = 0.5f;
float mod = 0.01f;

const float freq = 6.0f;

void legs(float t, float mul)
{
	glPushMatrix();
		glTranslatef(0.19f*mul, 0.0f, -0.015f);
		glRotateX(cosf(t)*13.0f-2.5f);
		glTranslatef(0.0f, -0.7f, 0.0f);
		glPushMatrix();
			glScalef(0.1f, 0.25f, 0.1f);
			cube();
		glPopMatrix();

		float m = -min(0.0f, cosf(t+M_PI/2.0f));
		glTranslatef(0.0f, m*0.15f - 0.52f, m*0.015f - 0.06f);
		glRotateX(10.0f);
		glPushMatrix();
			glScalef(0.1f, 0.3f, 0.1f);
			cube();
		glPopMatrix();

		glTranslatef(0.0f, -0.3f, 0.1f);
		glPushMatrix();
			glScalef(0.1f, 0.03f, 0.2f);
			cube();
		glPopMatrix();
	glPopMatrix();
}

void arms(float t, float mul)
{
	glPushMatrix();
		glTranslatef(0.24f*mul, 0.4f, 0.0f);
		glRotateZ(30.0f*mul);
		glRotateX(cosf(t)*20.0f+180.0f);
		glTranslatef(0.0f, 0.3f, 0.0f);
		glPushMatrix();
			glScalef(0.1f, 0.3f, 0.1f);
			cube();
		glPopMatrix();

		glTranslatef(0.0f, 0.22f, 0.0f);
		glRotateY(fabsf(cosf(t))*16.0f*mul); // mouvement sympa mais pas obligatoire du tout...
		glRotateX(100.0f);
		glRotateZ(165.0f*mul);
		glTranslatef(0.0f, 0.21f, 0.0f);
		glPushMatrix();
			glScalef(0.09f, 0.27f, 0.09f);
			cube();
		glPopMatrix();
	glPopMatrix();
}

void robot(float t)
{
	// head
	glPushMatrix();
		glTranslatef(0.0f, 0.71f+0.05f*fabsf(sinf(t)), 0.04f);
		glRotateX(-5.0f+10.0f*fabsf(cosf(t)));
		glScalef(0.2f, 0.2f, 0.2f);
		cube();
	glPopMatrix();

	// body
	glPushMatrix();
		glTranslatef(0.0f, 0.05f*fabsf(sinf(t)), 0.0f);
		glRotateY(2.5f-5.0f*cosf(t)); // obligatoire...
		glScalef(0.3f, 0.5f, 0.17f);
		cube();
	glPopMatrix();

	// arms
	glPushMatrix();
	arms(t, -1.0f);
	arms(t+(M_PI/2.0f)*freq, 1.0f);
	glPopMatrix();

	// legs
	glPushMatrix();
	legs(t, -1.0f);
	legs(t+(M_PI/2.0f)*freq, 1.0f);
	glPopMatrix();
}

void quad()
{
	glVertex3f(-1, -1, 0);
	glVertex3f( 1, -1, 0);
	glVertex3f( 1,  1, 0);
	glVertex3f(-1,  1, 0);
}

#define b(x) (x/255.0f)
void sonic(float t)
{
	bool c = false;
	for ( float y = -10.0f ; y < 11.0f ; y++ ) {
		for ( float x = -10.0f ; x < 11.0f ; x++ ) {
			if ( c )
				glColor3f(b(215), b(100), b(10));
			else
				glColor3f(b(10), b(70), b(200));
			c = !c;
//			glTranslate3f();
//			glRotatef(, 1, 0, 0);
//			glRotatef(, 0, 1, 0);
			quad();
		}
		c = !c;
	}
}

#undef main
int main()
{
#if 0
	bool running = true;
	SDL_Event event;
	SDL_Surface * screen;
	float time = 0.0f;
	float rotation = 0.0f;
	bool mousedown = false;

	SDL_Init(SDL_INIT_EVERYTHING);

	screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_OPENGL);
	SDL_WM_SetCaption("Robot !", "");

	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 100.0f);

	glMatrixMode(GL_MODELVIEW);

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_POLYGON_SMOOTH);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	static float ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	static float diffuse[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	static float position[] = { 2.0f, 4.0f, -2.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	unsigned int tick = SDL_GetTicks();

	while ( running ) {
		while ( SDL_PollEvent(& event) ) {
			if ( event.type == SDL_QUIT )
				running = false;
			else if ( event.type == SDL_KEYDOWN ) {
				if ( event.key.keysym.sym == SDLK_ESCAPE )
					running = false;
			} else if ( event.type == SDL_MOUSEBUTTONDOWN ) {
				if ( event.button.button == 1 )
					mousedown = true;
				else if ( event.button.button == 4 ) {
					param += mod;
					printf("param = %f\n", param);
				} else if ( event.button.button == 5 ) {
					param -= mod;
					printf("param = %f\n", param);
				}
			} else if ( event.type == SDL_MOUSEBUTTONUP ) {
				if ( event.button.button == 1 )
					mousedown = false;
			} else if ( event.type == SDL_MOUSEMOTION ) {
				if ( mousedown )
					rotation += event.motion.xrel;
			}
		}

		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
		glLoadIdentity();

		glTranslatef(0.0f, 0.0f, -5.0f);
		glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(rotation, 0.0f, 1.0f, 0.0f);

		robot(time * freq);

		SDL_GL_SwapBuffers();

		time = ((float) SDL_GetTicks() - (float) tick) / 1000.0f;
	}

	SDL_Quit();
#endif

	int a = 42;
	printf("%d\n", (a ^ -1)+1);
	system("pause");

	return 0;
}
