// header files
#include <GL/freeglut.h>

#define _USE_MATH_DEFINES
#include <math.h>

// global variable declarations
bool bIsFullScreen = false;

void Points()
{
	/*
	glBegin(GL_POINTS);
	int x, y;
	
	//X Axis points
	x = -1;
	y = 0;
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(1.0);
	while (x < 1)
	{
		glVertex2f(x, y);
		x += 0.2;
	}

	//Y axis points
	x = 0;
	y = -1;
	while (y < 1)
	{
		glVertex2f(x, y);
		y += 0.2;
	}
	*/
	glBegin(GL_POINTS);
	glPointSize(10);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(-0.5, 0.5);
	glEnd();
//	glFlush();

}
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
void Rocket()
{
	glBegin(GL_POLYGON);
	
	//middle Cylinder
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(-0.045, -0.75, 0.0);//bottom left
	glVertex3f(-0.045, -0.20, 0.0);//top left
	glVertex3f(0.045, -0.20, 0.0);//top right
	glVertex3f(0.045, -0.75, 0.0);//bottom right
	glEnd();
	
	//left Cylinder
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(-0.0675, -0.75, 0.0);//bottom left
	glVertex3f(-0.0675, -0.40, 0.0);//top left
	glVertex3f(-0.045, -0.40, 0.0);//top right
	glVertex3f(-0.045, -0.75, 0.0);//bottom right
	glEnd();

	//right Cylinder
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(0.045, -0.75, 0.0);//bottom left
	glVertex3f(0.045, -0.40, 0.0);//top left
	glVertex3f(0.0675, -0.20, 0.0);//top right
	glVertex3f(0.0675, -0.75, 0.0);//bottom right
	glEnd();

	
}



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
	glutCreateWindow("Rocket");

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
	glClear(GL_COLOR_BUFFER_BIT);
	

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
	GridLines();
	//Rocket();

	Points();


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

