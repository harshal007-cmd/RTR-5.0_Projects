// Header Files
#include <GL/freeglut.h>

// Global variable declarations
bool bIsFullScreen = false;

// Entry-point function
int main(int argc, char* argv[])
{
	// Function declarations
	void initialize(void);
	void resize(int, int);
	void display(void);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void uninitialize(void);


	// code
	glutInit(&argc, argv);  //Init(initialization)
  
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);


	glutInitWindowSize(800, 600); //(800x600), 800-width, 600-height
	glutInitWindowPosition(100, 100); //
	glutCreateWindow("Street Lamp");

	initialize();

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutCloseFunc(uninitialize);

	glutMainLoop();

	return 0;
}

void initialize(void)
{
	//code
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void resize(int width, int height)
{
	//code
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void StreetLamp(void)
{
	glBegin(GL_QUADS);

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.036f, 0.84f);
	glVertex2f(0.036f, 0.84f);
	glVertex2f(0.036f, 0.82f);
	glVertex2f(-0.036f, 0.82f);
	glEnd();

	//Trapezium above Yellow Part's Block
	glBegin(GL_POLYGON);

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.04f, 0.82f);
	glVertex2f(0.04f, 0.82f);
	glVertex2f(0.086f, 0.72f);
	glVertex2f(-0.086f, 0.72f);
	glEnd();


	//Block Above Yellow Part
	glBegin(GL_QUADS);

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.09f, 0.72f);
	glVertex2f(0.09f, 0.72f);
	glVertex2f(0.09f, 0.7f);
	glVertex2f(-0.09f, 0.7f);
	glEnd();

	//Yellow Part(Light)
	glBegin(GL_POLYGON);

	glColor3f(1.0f, 3.22f, 0.0f);
	glVertex2f(-0.09f, 0.7f);
	glVertex2f(0.09f, 0.7f);
	glVertex2f(0.05f, 0.5f);
	glVertex2f(-0.05f, 0.5f);
	glEnd();

	glBegin(GL_LINE_LOOP);

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.09f, 0.7f);
	glVertex2f(0.09f, 0.7f);
	glVertex2f(0.05f, 0.5f);
	glVertex2f(-0.05f, 0.5f);
	glEnd();

	// Line On Top Of Block 
	glBegin(GL_POLYGON);

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.005f, 0.7f);
	glVertex2f(0.005f, 0.7f);
	glVertex2f(0.005f, 0.5f);
	glVertex2f(-0.005f, 0.5f);
	glEnd();

	//Block on top of Light Pole
	glBegin(GL_QUADS);

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.05f, 0.5f);
	glVertex2f(0.05f, 0.5f);
	glVertex2f(0.05f, 0.48f);
	glVertex2f(-0.05f, 0.48f);
	glEnd();

	// Light Pole
	glBegin(GL_POLYGON);

	glColor3f(0.0f, 0.0f, 0.0f); // color (grey) 
	glVertex2f(-0.007f, 0.5f);
	glVertex2f(0.007f, 0.5f);
	glVertex2f(0.007f, -0.5f);
	glVertex2f(-0.007f, -0.5f);
	glEnd();

	//Block Above Pole
	glBegin(GL_QUADS);

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.04f, -0.3f);
	glVertex2f(0.04f, -0.3f);
	glVertex2f(0.04f, -0.52f);
	glVertex2f(-0.04f, -0.52f);
	glEnd();

	// Base
	glBegin(GL_QUADS);

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.09f, -0.5f);
	glVertex2f(0.09f, -0.5f);
	glVertex2f(0.09f, -0.55f);
	glVertex2f(-0.09f, -0.55f);
	glEnd();
}


void display(void)
{
	//code
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	StreetLamp();

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
