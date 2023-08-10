// header files
#include <GL/freeglut.h>

#define _USE_MATH_DEFINES
#include <math.h>

// global variable declarations
bool bIsFullScreen = false;

void cloud(void);	// Clouds

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

	glutInitWindowSize(800, 800);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Clouds");

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

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(0.5f, 0.75f, 0.0f);
	cloud();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.7f, 0.35f, 0.0f);
	cloud();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.7f, 0.75f, 0.0f);
	cloud();
	glPopMatrix();	

	glPushMatrix();
	glTranslatef(0.7f, 0.20f, 0.0f);
	cloud();
	glPopMatrix();


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

// cloud()
void cloud(void)
{	
	glScalef(0.5f, 0.5f, 0.0f);

	glColor3f(0.529, 0.808, 0.922); // SkyBlue

	glBegin(GL_QUADS); // Rectangle 

	glVertex3f(-0.3f, -0.18f, 0.0f);		// Q3
	glVertex3f(-0.3f, 0.15f, 0.0f);			// Q2
	glVertex3f(0.3f, 0.15f, 0.0f);			// Q1
	glVertex3f(0.3f, -0.18f, 0.0f);			// Q4
	
	glEnd();

	glBegin(GL_POLYGON);			// Circle 1

	float radius_1 = 0.18f;
	float x_centre_1 = -0.30f;
	float y_centre_1 = 0.00f;
	for (int i = 0; i < 1000; i++)
	{
		float angle = 2.0f * M_PI * i / 1000;
		glVertex2f(x_centre_1 + radius_1 * cos(angle), y_centre_1 + radius_1 * sin(angle));
		glColor3f(0.529, 0.808, 0.922); // SkyBlue
	}
	glEnd();

	glBegin(GL_POLYGON);			// Circle 2

	float radius_2 = 0.15f;
	float x_centre_2 = -0.10f;
	float y_centre_2 = 0.20f;
	for (int i = 0; i < 1000; i++)
	{
		float angle = 2.0f * M_PI * i / 1000;
		glVertex2f(x_centre_2 + radius_2 * cos(angle), y_centre_2 + radius_2 * sin(angle));
		glColor3f(0.529, 0.808, 0.922); // SkyBlue
	}
	glEnd();

	glBegin(GL_POLYGON);			// Circle 3

	float radius_3 = 0.20f;
	float x_centre_3 = 0.16f;
	float y_centre_3 = 0.26f;
	for (int i = 0; i < 1000; i++)
	{
		float angle = 2.0f * M_PI * i / 1000;
		glVertex2f(x_centre_3 + radius_3 * cos(angle), y_centre_3 + radius_3 * sin(angle));
		glColor3f(0.529, 0.808, 0.922); // SkyBlue
	}
	glEnd();

	glBegin(GL_POLYGON);			// Circle 4

	float radius_4 = 0.18f;
	float x_centre_4 = 0.30f;
	float y_centre_4 = 0.00f;
	for (int i = 0; i < 1000; i++)
	{
		float angle = 2.0f * M_PI * i / 1000;
		glVertex2f(x_centre_4 + radius_4 * cos(angle), y_centre_4 + radius_4 * sin(angle));
		glColor3f(0.529, 0.808, 0.922); // SkyBlue
	}
	glEnd();
}







