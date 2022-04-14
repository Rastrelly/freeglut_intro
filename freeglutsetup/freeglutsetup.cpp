#include <iostream>
#include <GL/freeglut.h>

using namespace std;

//стартові значення розміру вікна
int ww = 800; int wh = 600;

bool needrefresh = false;

enum drawmode
{
	d_lines, d_linestrip, d_triangles, d_quads
} dm;

void render();
void initfreeglut(int argc, char **argv);
void prepareopengl();
void requestdrawmode();
void idle();
void resize(int w, int h);

// головна функція
int main(int argc, char **argv)
{
	requestdrawmode();
	initfreeglut(argc, argv);
	prepareopengl();
	glutMainLoop(); 
}


//зворотні виклики
void render()
{

	cout << "Render\n";

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

	glLineWidth(1);
	glColor3f(1.0f, 1.0f, 1.0f);
	
	if (dm == d_lines)
	{
		glBegin(GL_LINES);
			glVertex2f(-.5f, -.5f);
			glVertex2f(.5f, -.5f);

			glVertex2f(.5f, -.5f);
			glVertex2f(.5f, .5f);

			glVertex2f(.5f, .5f);
			glVertex2f(-.5f, .5f);

			glVertex2f(-.5f, .5f);
			glVertex2f(-.5f, -.5f);
		glEnd();
	}
	
	if (dm == d_linestrip)
	{
		glBegin(GL_LINE_STRIP);
			glVertex2f(-.5f, -.5f);
			glVertex2f(.5f, -.5f);

			glVertex2f(.5f, .5f);

			glVertex2f(-.5f, .5f);

			glVertex2f(-.5f, -.5f);
		glEnd();
	}

	if (dm == d_triangles)
	{
		glBegin(GL_TRIANGLES);
			glVertex2f(-.5f, -.5f);
			glVertex2f(.5f, -.5f);
			glVertex2f(-.5f, .5f);

			glVertex2f(.5f, -.5f);
			glVertex2f(-.5f, .5f);
			glVertex2f(.5f, .5f);
		glEnd();
	}

	if (dm == d_quads)
	{
		glBegin(GL_QUADS);
			glVertex2f(-.5f, -.5f);
			glVertex2f(.5f, -.5f);
			glVertex2f(.5f, .5f);
			glVertex2f(.5f, -.5f);
		glEnd();
	}

	
	glLineWidth(4);
	glColor3f(1, 0, 0);
	double rng = 9.9;
	
	while (rng > 0)
	{
		glBegin(GL_LINE_STRIP);
			glVertex2d(-rng, -rng);
			glVertex2d(rng, -rng);
			glVertex2d(rng, rng);
			glVertex2d(-rng, rng);
			glVertex2d(-rng, -rng);
		glEnd();
		rng -= 1;
	}

	glPopMatrix();

	glutSwapBuffers();

	
}

void idle()
{
	if (needrefresh)
	{
		render();
		needrefresh = false;
	}
}

void resize(int w, int h)
{
	cout << "Resize\n";

	ww = w; wh = h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//встановлюємо розмір в'юпорту в пропорції
	//до розміру вікна
	glViewport(0, 0, w, h);

	double ow = 10; double oh = 10;

	if (w > h)
	{
		ow = 10;
		oh = 10 * ((double)h / (double)w);
	}
	else
	{
		ow = 10 * ((double)w / (double)h);
		oh = 10;
	}

	gluOrtho2D(-1 * (double)ow / 2, (double)ow / 2,
		-1 * (double)oh / 2, (double)oh / 2);

	needrefresh = true;

}

//ініціалізатори
void initfreeglut(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(120,120);
	glutInitWindowSize(ww, wh);
	glutCreateWindow("Hello World");	
	glutIdleFunc(idle);
	glutReshapeFunc(resize);
	glutDisplayFunc(render);
}

void prepareopengl()
{
	glClearColor(0.1, 0.1, 0.1, 1.0);
	glEnable(GL_DOUBLEBUFFER);
}

void requestdrawmode()
{
	cout << "Select draw mode:\n1 - lines; 2 - line strip; 3 - triangles;" <<
		" 4 - quads\n";
	int a = 0;
	cin >> a;
	if (a < 1) a = 1;
	if (a > 4) a = 4;
	dm = (drawmode)(a - 1);
}

