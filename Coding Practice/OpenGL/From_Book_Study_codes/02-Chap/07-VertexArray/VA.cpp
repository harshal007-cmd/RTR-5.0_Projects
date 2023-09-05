#include<GL\freeglut.h>
#include<math.h>
int bIsScreenFull = false;


void shape()
{
	static GLfloat vertices[] = { 0.25, 0.25,
								0.100, 0.325,
								1.75, 0.25,
								1.75, 3.25,
								2.50, 0.25,
								3.25, 3.25 };
	static GLfloat colors[] = { 1.0, 0.2, 0.2,
								0.2, 0.2, 1.0,
								0.8, 1.0, 0.2,
								0.75, 0.75, 0.75,
								0.35, 0.35, 0.35,
								0.5, 0.5, 0.5 };

	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(2, GL_INT, 0, vertices);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	shape();
	//PolyMode();

	glutSwapBuffers();
}
/*
void update(int val)
{
	static int flag = 0;

	if (t < 1.0 && flag == 0)
	{
		t += 0.005f;
		if (t >= 1.0)
			flag = 1;
	}
	else if (t > 0.0f && flag == 1)
	{
		t -= 0.005f;
		if (t <= 0.0f)
			flag = 0;
	}
	
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, update, 0);
}
*/
int main(int argc, char* argv[])
{
	void initialize(void);
	void display(void);
	void resize(int, int);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void uninitialize(void);

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800,700);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("My practice window: The Great Harshal");

	initialize();

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
//	glutTimerFunc(1000 / 60, update, 0);
	glutCloseFunc(uninitialize);

	glutMainLoop();

	return 0;


}

void initialize(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

}

void resize(int width, int height) {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}



void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{	
	case 27:
		glutLeaveMainLoop();
			break;
	case 'F':
	case 'f':
		if (bIsScreenFull == false)
		{
			glutFullScreen();
			bIsScreenFull = true;
		}
		else
		{
			glutLeaveFullScreen();
			bIsScreenFull = false;
		}
		break;

	default:
		break;
	}
}

void mouse(int button, int state, int x, int y)
{
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

}
