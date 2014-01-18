// g++ -I /usr/include/SDL -o fs fs.cpp -lSDL -lGL -lGLU -lm

#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

void quad(float x0, float y0, float z0,
			float x1, float y1, float z1,
			float x2, float y2, float z2,
			float x3, float y3, float z3)
{
	float vx1 = x1 - x0;
	float vx2 = x2 - x0;
	float vy1 = y1 - y0;
	float vy2 = y2 - y0;
	float vz1 = z1 - z0;
	float vz2 = z2 - z0;
	glNormal3f(vy1 * vz2 - vz1 * vy2, vz1 * vx2 - vx1 * vz2, vx1 * vy2 - vy1 * vx2);
	glVertex3f(x0, y0, z0);
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y2, z2);
	glVertex3f(x3, y3, z3);
}

void drawFlyingSaucer(const float res = 12.0)
{
	static const int nb = 9;
	static const float h[nb] = { 1.0, 0.9, 0.8, 0.5, 0.4, 0.3, 0.15, 0.01, 0.0 };
	static const float r[nb] = { 0.001, 0.2, 0.3, 0.4, 0.8, 1.0, 0.8, 0.5, 0.0 };

glBegin(GL_QUADS);
glColor3f(0.5, 0.5, 0.5);
for ( int i = 0 ; i < nb - 1 ; i++ ) {
for ( float j = 0.0 ; j < 2.0 * M_PI ; j += 2.0 * M_PI / res ) {
	quad(cosf(j)*r[i], h[i], sinf(j)*r[i],
			cosf(j+2.0*M_PI/res)*r[i], h[i], sinf(j+2.0*M_PI/res)*r[i],
			cosf(j+2.0*M_PI/res)*r[i+1], h[i+1], sinf(j+2.0*M_PI/res)*r[i+1],
			cosf(j)*r[i+1], h[i+1], sinf(j)*r[i+1]);
}
}
glEnd();
}

int main(int argc, char ** argv)
{
	bool running = true;
	SDL_Event event;
	float ry = 0.0;
	float rz = 0.0;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_Surface * screen = SDL_SetVideoMode(640, 480, 32, SDL_OPENGL|SDL_HWSURFACE);
	SDL_WM_SetCaption("Flying Saucer !", "");
	
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, (float[]) { 1.0, 1.0, 1.0 });
	glLightfv(GL_LIGHT0, GL_DIFFUSE, (float[]) { 1.0, 1.0, 1.0 });
	glLightfv(GL_LIGHT0, GL_POSITION, (float[]) { 0.0, 20.0, 0.0 });

	glViewport(0, 0, 640, 480);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 640.0 / 480.0, 0.5, 100.0);
	glMatrixMode(GL_MODELVIEW);

	while ( running ) {
		while ( SDL_PollEvent(& event) ) {
			if ( event.type == SDL_QUIT || (event.type == SDL_KEYDOWN
						&& event.key.keysym.sym == SDLK_ESCAPE ) )
				running = false;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		glTranslated(2.0*cosf(rz), 2.0*sinf(rz), -10.0);
		rz += 0.001;
		glRotatef(ry, 0.0, 1.0, 0.0);
		ry += 0.1;
		drawFlyingSaucer();
		glRotatef(ry/5.0, 0.0, 1.0, 0.5);
		glTranslatef(1.0, 2.0*cosf(ry/100.0), -3.0+cosf(rz/50.0));
		drawFlyingSaucer(70.0);

		SDL_GL_SwapBuffers();
	}

	SDL_FreeSurface(screen);
	SDL_Quit();

	return 0;
}
