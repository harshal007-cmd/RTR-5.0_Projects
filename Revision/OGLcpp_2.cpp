// header files
#include <GL/freeglut.h>


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
	glutCreateWindow("LOGO's:");

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
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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

	GLfloat scale = 0.1f;
	
	//Big triangle
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);

	glVertex3f(3.0 * scale, -1.7320 * scale, 0.0);
	glVertex3f(-3.0 * scale, -1.7320 * scale, 0.0);
	glVertex3f(0.0 * scale, 3.464 * scale, 0.0);
	
	//left white
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(0.0 * scale, 0.0 * scale, 0.0);
	glVertex3f(-2.0 * scale, 0.0 * scale, 0.0);
	glVertex3f(-1.0 * scale, 1.7320 * scale, 0.0);

	//right white
	glVertex3f(0.0 * scale, 0.0 * scale, 0.0);
	glVertex3f(2.0 * scale, 0.0 * scale, 0.0);
	glVertex3f(1.0 * scale, 1.7320 * scale, 0.0);

	//down white
	glVertex3f(0.0 * scale, 0.0 * scale, 0.0);
	glVertex3f(-1.0 * scale, -1.7320 * scale, 0.0);
	glVertex3f(1.0 * scale, -1.7320 * scale, 0.0);

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
