// Header files
#include <GL/freeglut.h>

//global variable declaration
bool bIsFullScreen = false;

void GridLines()
{
	
	//grid lines
	glBegin(GL_LINES);
	glColor3f(0.0, 0.8, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, -1.0, 0.0);
	glEnd();

}

//entry-point function
void background_mountain()
{
	//sky
	glBegin(GL_POLYGON);
	glColor3f(135.0 / 255.0, 206.0 / 255.0, 235.0 / 255.0);
	glVertex3f(-1.0, 0.1, 0.0);

	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(-1.0, 1.0, 0.0);
	glVertex3f(1.0, 1.0, 0.0);
	
	glColor3f(135.0 / 255.0, 206.0 / 255.0, 235.0 / 255.0);
	glVertex3f(1.0, 0.1, 0.0);
	glEnd();

	//Mountains
	glBegin(GL_TRIANGLES);
	glColor3f(0, 245.0 / 255, 120.0 / 255);
	//1st
	glVertex3f(-1.0, 0.1, 0.0);
	glVertex3f(-0.4, 0.6, 0.0);
	glVertex3f(0.25, 0.1, 0.0);

	//2
	glColor3f(0, 255.0 / 255, 0.0);

	glVertex3f(0.0, 0.1, 0.0);
	glColor3f(0, 245.0 / 255, 120.0 / 255);

	glVertex3f(0.4, 0.4, 0.0);
	glVertex3f(1.0, 0.1, 0.0);
	glEnd();

	//ground
	glBegin(GL_POLYGON);
	glColor3f(196.0 / 255, 164.0 / 255, 132.0 / 255);
	glVertex3f(-1.0, -1.0, 0.0);
	glVertex3f(-1.0, 0.1, 0.0);
	glVertex3f(1.0, 0.1, 0.0);
	glVertex3f(1.0, -1.0, 0.0);
	glEnd();

	//river
	glBegin(GL_TRIANGLES);
	glColor3f(135.0 / 255.0, 206.0 / 255.0, 235.0 / 255.0);
	glVertex3f(0.0, 0.1, 0.0);
	glVertex3f(0.6, -1.0, 0.0);
	glVertex3f(0.22, -1.0, 0.0);

	glEnd();

}

void house()
{
	//base
	glBegin(GL_POLYGON);
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(-0.25, -0.7, 0.0);
	glVertex3f(-0.25, -0.65, 0.0);
	glVertex3f(0.25, -0.65, 0.0);
	glVertex3f(0.25, -0.7, 0.0);

	glEnd();

	//middle
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.5, 0.5);
	glVertex3f(-0.20, -0.65, 0.0);
	glVertex3f(-0.20, -0.35, 0.0);
	glVertex3f(0.20, -0.35, 0.0);
	glVertex3f(0.20, -0.65, 0.0);

	glEnd();

	//roof
	glBegin(GL_POLYGON);
	glColor3f(160.0/255, 82.0/255, 45.0/255);
	glVertex3f(-0.25, -0.35, 0.0);
	glVertex3f(-0.20, -0.20, 0.0);
	glVertex3f(0.20, -0.20, 0.0);
	glVertex3f(0.25, -0.35, 0.0);

	glEnd();

	//door
	glBegin(GL_POLYGON);
	glColor3f(210.0/255, 105.0/255, 30.0/255);
	glVertex3f(-0.05, -0.65, 0.0);
	glVertex3f(-0.05, -0.45, 0.0);
	glVertex3f(0.05, -0.45, 0.0);
	glVertex3f(0.05, -0.65, 0.0);

	glEnd();

	//window 1
	glBegin(GL_POLYGON);
	glColor3f(1.0,1.0,1.0);
	glVertex3f(-0.15, -0.40, 0.0);
	glVertex3f(-0.15, -0.45, 0.0);
	glVertex3f(-0.08, -0.45, 0.0);
	glVertex3f(-0.08, -0.40, 0.0);

	glEnd();

	//window 2
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(0.15, -0.40, 0.0);
	glVertex3f(0.15, -0.45, 0.0);
	glVertex3f(0.08, -0.45, 0.0);
	glVertex3f(0.08, -0.40, 0.0);

	glEnd();



}


int main(int argc, char* argv[])
{
	//function declarations
	void initialize(void);
	void resize(int, int);
	void display(void);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void uninitialize(void);

	//code
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Drawing using only Polygons");

	initialize();

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutCloseFunc(uninitialize);

	glutMainLoop();
	return (0);

}

void initialize(void)
{
	//code
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

void resize(int width, int height)
{
	//code
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

}

void display(void)
{
	//code
	glClear(GL_COLOR_BUFFER_BIT);

	background_mountain();
	
	glPushMatrix();
	glTranslatef(-0.4,-0.1,0.0);
	house();
	glPopMatrix();
	GridLines();
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	//code
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
	//code
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
	//code 
}

