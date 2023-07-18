// header files
#include <GL/freeglut.h>

#define _USE_MATH_DEFINES
#include <math.h>

// global variable declarations
bool bIsFullScreen = false;


// entry-point function
int main(int argc, char* argv[])
{
	// function declarations
	void initialize(void);
	void resize(int, int);
	void display(void);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void uninitialize(void);

	// code
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("My First RTR5 Program : Harshal Sali");

	initialize();

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutCloseFunc(uninitialize);

	glutMainLoop();

	return(0);
}
void initialize(void)
{
	// code
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
void resize(int width, int height)
{
	// code
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void display(void)
{
	// code
	glClear(GL_COLOR_BUFFER_BIT);
	/*  //Rose points code by Ganesh
	float radius = 0.4f;
	float angle;

	glColor3f(1.0f, 0.0f, 0.0f);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(3);
	glBegin(GL_POINTS);
	for (int i = 0;i < 300;++i)
	{
		angle = 2 * M_PI * i / 300;
		x=16 * sin(angle)
		radius = 0.5 * sin(5 * angle);
		glVertex2f(radius * cos(angle), radius * sin(angle));
	}
	*/
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin(GL_POLYGON);

	glColor3f(1.0, 0.0, 0.0);
	
	/*
	for (float t = 0.0; t <= 2 * 3.14159; t += 0.01) {
		float x = 16 * pow(sin(t), 3);
		float y = 13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t);
		glVertex2f(x / 100, y / 100);  // Scaling down the coordinates
	}
	*/
	for (int i = 0;i < 100;++i)
	{
		float angle = 2 * 3.14159 * i / 100;
		float x = 16 * pow(sin(angle), 3);
		float y = 16 * cos(angle) - 7 * cos(2 * angle) -2 * cos(3 * angle) - cos(4 * angle);
		glVertex2f(x / 25, y / 25);
	}
	

	glEnd();

	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	// code
	switch (key)
	{
	case 27:
		glutLeaveMainLoop();
		break;
	case 'F':
	case 'f':
		if (bIsFullScreen == false)
		{
			glutFullScreen();
			bIsFullScreen = true;
		}
		else
		{
			glutLeaveFullScreen();
			bIsFullScreen = false;
		}
		break;
	default:
		break;
	}
}

void mouse(int button, int state, int x, int y)
{
	// code
	switch (button)
	{
	case GLUT_RIGHT_BUTTON:
		glutLeaveMainLoop();
		break;
	default:
		break;
	}

}

void uninitialize(void)
{
	// code
}
