#include <GL/freeglut.h>

// Global Variable Declarations
bool bIsFullScreen = false;

// Entry-Point Function
int main(int argc, char* argv[])
{
	// Function Declarations
	void initialize(void);
	void resize(int, int);
	void display(void);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void uninitialize(void);

	// Code
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("My House: Krishna Rai Prakash");

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
	// Code
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void resize(int width, int height)
{
	// Code
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void display(void)
{
	void Ground(void);

	// Code
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Ground();

	glutSwapBuffers();
}

void Ground(void)
{
	//left ground
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex3f(-1.0f, -0.5f, 0.0f);
	glVertex3f(-0.2f, -0.5f, 0.0f);
	glVertex3f(-0.3f, -1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glEnd();

	//right ground
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex3f(0.2f, -0.5f, 0.0f);
	glVertex3f(1.0f, -0.5f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(0.3f, -1.0f, 0.0f);
	glEnd();

	//road
	glBegin(GL_POLYGON);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.2f, -0.5f, 0.0f);
	glVertex3f(0.2f, -0.5f, 0.0f);
	glVertex3f(0.3f, -1.0f, 0.0f);
	glVertex3f(-0.3f, -1.0f, 0.0f);
	glEnd();

	//divider
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-0.0015f, -0.5f, 0.0f);
	glVertex3f(0.0015f, -0.5f, 0.0f);
	glVertex3f(0.0015f, -0.65f, 0.0f);
	glVertex3f(-0.0015f, -0.65f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-0.0015f, -0.67f, 0.0f);
	glVertex3f(0.0015f, -0.67f, 0.0f);
	glVertex3f(0.0018f, -0.85f, 0.0f);
	glVertex3f(-0.0018f, -0.85f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-0.0018f, -0.87f, 0.0f);
	glVertex3f(0.0018f, -0.87f, 0.0f);
	glVertex3f(0.002f, -1.0f, 0.0f);
	glVertex3f(-0.002f, -1.0f, 0.0f);
	glEnd();

	// left bench 1
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.7f, 0.0f);
	glVertex3f(-0.9f, -0.4f, 0.0f);
	glVertex3f(-0.7f, -0.4f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.7f, -0.42f, 0.0f);
	glVertex3f(-0.9f, -0.42f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.7f, 0.0f);
	glVertex3f(-0.9f, -0.43f, 0.0f);
	glVertex3f(-0.7f, -0.43f, 0.0f);
	//glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.7f, -0.45f, 0.0f);
	glVertex3f(-0.9f, -0.45f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.6f, 0.0f);
	glVertex3f(-0.9f, -0.47f, 0.0f);
	glVertex3f(-0.7f, -0.47f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.7f, -0.48f, 0.0f);
	glVertex3f(-0.9f, -0.48f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.6f, 0.0f);
	glVertex3f(-0.89f, -0.485f, 0.0f);
	glVertex3f(-0.71f, -0.485f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.71f, -0.495f, 0.0f);
	glVertex3f(-0.89f, -0.495f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.6f, 0.0f);
	glVertex3f(-0.89f, -0.505f, 0.0f);
	glVertex3f(-0.71f, -0.505f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.71f, -0.515f, 0.0f);
	glVertex3f(-0.89f, -0.515f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.6f, 0.0f);
	glVertex3f(-0.89f, -0.48f, 0.0f);
	glVertex3f(-0.88f, -0.48f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.88f, -0.525f, 0.0f);
	glVertex3f(-0.89f, -0.525f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.6f, 0.0f);
	glVertex3f(-0.71f, -0.48f, 0.0f);
	glVertex3f(-0.72f, -0.48f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.71f, -0.525f, 0.0f);
	glVertex3f(-0.72f, -0.525f, 0.0f);
	glEnd();

	// right bench 1
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.7f, 0.0f);
	glVertex3f(0.9f, -0.4f, 0.0f);
	glVertex3f(0.7f, -0.4f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.7f, -0.42f, 0.0f);
	glVertex3f(0.9f, -0.42f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.7f, 0.0f);
	glVertex3f(0.9f, -0.43f, 0.0f);
	glVertex3f(0.7f, -0.43f, 0.0f);
	//glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.7f, -0.45f, 0.0f);
	glVertex3f(0.9f, -0.45f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.6f, 0.0f);
	glVertex3f(0.9f, -0.47f, 0.0f);
	glVertex3f(0.7f, -0.47f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.7f, -0.48f, 0.0f);
	glVertex3f(0.9f, -0.48f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.6f, 0.0f);
	glVertex3f(0.89f, -0.485f, 0.0f);
	glVertex3f(0.71f, -0.485f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.71f, -0.495f, 0.0f);
	glVertex3f(0.89f, -0.495f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.6f, 0.0f);
	glVertex3f(0.89f, -0.505f, 0.0f);
	glVertex3f(0.71f, -0.505f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.71f, -0.515f, 0.0f);
	glVertex3f(0.89f, -0.515f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.6f, 0.0f);
	glVertex3f(0.89f, -0.48f, 0.0f);
	glVertex3f(0.88f, -0.48f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.88f, -0.525f, 0.0f);
	glVertex3f(0.89f, -0.525f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.6f, 0.0f);
	glVertex3f(0.71f, -0.48f, 0.0f);
	glVertex3f(0.72f, -0.48f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.71f, -0.525f, 0.0f);
	glVertex3f(0.72f, -0.525f, 0.0f);
	glEnd();
}

void keyboard(unsigned char key, int x, int y)
{
	// Code
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
	// Code
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
	// Code
}

