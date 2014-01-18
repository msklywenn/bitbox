#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#define WIDTH 1024
#define HEIGHT 768

void color(float r, float g, float b)
{
	glColor4fv(
			(float []){r, g, b, 1.0f});
}

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

const float freq = 6.4f;

void legs(float t, bool i)
{
	float x[2] = { 0.19f, -0.19f };

	glPushMatrix();
	glTranslatef(x[i], -0.1f, 0.0f);
	glRotatef(cosf(t)*10.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -0.7f, 0.0f);
	glScalef(0.1f, 0.4f, 0.1f);
	cube();
	glPopMatrix();
}

void arms(float t, bool i)
{
	float x[2] = { 0.24f, -0.24f };
	float r[2] = { -40.0f, 40.0f };

	glPushMatrix();
	glTranslatef(x[i], 0.4f, 0.0f);
	glRotatef(cosf(t)*15.0f+r[i], 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, 0.3f, 0.0f);
	glScalef(0.1f, 0.3f, 0.1f);
	cube();
	glPopMatrix();
}

void robot(float t)
{
	// head
	//color(1.0f, 1.0f, 1.0f);
	glPushMatrix();
		glTranslatef(0.0f, 0.71f+0.05f*fabsf(sinf(t)), 0.04f);
		glRotatef(-5.0f+10.0f*fabsf(cosf(t)), 1.0f, 0.0f, 0.0f);
		glScalef(0.2f, 0.2f, 0.2f);
		cube();
	glPopMatrix();

	// body
	//color(0.5f, 0.5f, 1.0f);
	glPushMatrix();
		glTranslatef(0.0f, 0.05f*fabsf(sinf(t)), 0.0f);
		glRotatef(-2.5f+5.0f*fabsf(cosf(t)), 0.0f, 1.0f, 0.0f);
		glScalef(0.3f, 0.5f, 0.17f);
		cube();
	glPopMatrix();

	// arms
	//color(1.0f, 0.5f, 0.5f);
	glPushMatrix();
	arms(t, false);
	arms(t, true);
	glPopMatrix();
	
	// legs
	//color(0.5f, 1.0f, 0.5f);
	glPushMatrix();
	legs(t, false);
	legs(t+(M_PI/2.0f)*freq, true);
	glPopMatrix();
}

int main()
{
	bool running = true;
	SDL_Event event;
	SDL_Surface * screen;
	float time;
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
	glLightfv(GL_LIGHT0, GL_AMBIENT, (float []) { 0.1f, 0.1f, 0.1f, 1.0f } );
	glLightfv(GL_LIGHT0, GL_DIFFUSE, (float []) { 0.1f, 0.1f, 0.1f, 1.0f } );

	glLightfv(GL_LIGHT0, GL_POSITION, (float []) { 2.0f, 4.0f, -2.0f } );

	unsigned int tick = SDL_GetTicks();

	while ( running ) {
		while ( SDL_PollEvent(& event) ) {
			if ( event.type == SDL_QUIT )
				running = false;
			else if ( event.type == SDL_KEYDOWN ) {
				if ( event.key.keysym.sym == SDLK_ESCAPE )
					running = false;
			} else if ( event.type == SDL_MOUSEBUTTONDOWN ) {
				mousedown = true;
			} else if ( event.type == SDL_MOUSEBUTTONUP ) {
				mousedown = false;
			} else if ( event.type == SDL_MOUSEMOTION ) {
				if ( mousedown )
					rotation += event.motion.xrel;
			}
		}

		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
		glLoadIdentity();

		glTranslatef(0.0f, 0.0f, -4.0f);
		glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(rotation, 0.0f, 1.0f, 0.0f);

		robot(time * freq);

		SDL_GL_SwapBuffers();

		time = ((float) SDL_GetTicks() - (float) tick) / 1000.0f;
	}

	SDL_Quit();

	return 0;
}
