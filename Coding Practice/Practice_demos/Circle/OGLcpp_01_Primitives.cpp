// header files
#include <GL/freeglut.h>
#include <stdlib.h>
#include <time.h>

// global variable declarations
bool bIsFullScreen = false;

GLenum currenttype = GL_TRIANGLES;

GLfloat MyRand(GLfloat min, GLfloat max)
{
	return min + rand() / (RAND_MAX / (max - min));
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

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("My First RTR5 Program : Srushti Umesh Moghe");

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

	srand(time(NULL));

	glClear(GL_COLOR_BUFFER_BIT);
	switch (currenttype)
	{
		case GL_POINTS:
			
			glEnable(GL_POINT_SMOOTH);

			glPointSize(50);

			glBegin(currenttype);

			for (int i = 0; i < 20; i++)
			{

				glColor3f(MyRand(0.0f, 1.0f), MyRand(0.0f, 1.0f), MyRand(0.0f, 1.0f));

				glVertex2f(MyRand(-1.0f, 1.0f), MyRand(-1.0f, 1.0f));
			}

			glEnd();
			

		case GL_LINES:

			glEnable(GL_LINE_SMOOTH);

			glLineWidth(25);

			glBegin(currenttype);

			for (int i = 0; i < 20; i++)
			{

				glColor3f(MyRand(0.0f, 1.0f), MyRand(0.0f, 1.0f), MyRand(0.0f, 1.0f));

				glVertex2f(MyRand(-1.0f, 1.0f), MyRand(-1.0f, 1.0f));
			}

			glEnd();

		case GL_TRIANGLES:

			glBegin(currenttype);

			for (int i = 0; i < 9; i++)
			{

				glColor3f(MyRand(0.0f, 1.0f), MyRand(0.0f, 1.0f), MyRand(0.0f, 1.0f));

				glVertex2f(MyRand(-1.0f, 1.0f), MyRand(-1.0f, 1.0f));
			}

			glEnd();

			break;
		default:
			break;
	}

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
