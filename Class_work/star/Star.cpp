// Header files
#include <GL/freeglut.h>

//global variable declaration
bool bIsFullScreen = false;

//entry-point function
void star() 
{
	glBegin(GL_TRIANGLES);
	//1 down tri
	glColor3f(0.8, 0.9, 0.9);
	glVertex3f(-0.36, -0.36, 0.0);//BL
	glVertex3f(0.0, 0.42, 0.0);//T
	glVertex3f(0.36, -0.36, 0.0);//RL

	//2 upper tri
	glColor3f(0.8, 0.9, 0.9);
	glVertex3f(0.0, -0.54, 0.0);//D
	glVertex3f(-0.32, 0.24, 0.0);//TL
	glVertex3f(0.32, 0.24, 0.0);//TR

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
	glutCreateWindow("My First RTR 5 Program : Harshal Vijay Sali");

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

	star();


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

