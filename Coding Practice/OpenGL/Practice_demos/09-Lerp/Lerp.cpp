#include<GL\freeglut.h>
#include<math.h>
int bIsScreenFull = false;

static GLfloat t = 0.0f;

float lerp1(float start, float end, float t)
{
	return start + t * (end - start);
}

void update(int val)
{
	if (t < 1.0)
		t += 0.005f;
	if (t == 1.0)
		t -= 0.005f;
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, update, 0);
}

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
	glutTimerFunc(1000 / 60, update, 0);
	glutCloseFunc(uninitialize);

	glutMainLoop();

	return 0;


}

void initialize(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

void resize(int width, int height) {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SIZE);
	
	glLineWidth(5.0);
	glBegin(GL_LINES);
		glColor3f(lerp1(1.0,0.0,t), 0.0, 0.0);
		glVertex2f(-0.5, 0.0);
		glVertex2f(0.5, 0.0);
	glEnd();

	glPointSize(20.0);
	glBegin(GL_POINTS);
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(0.0, 0.0);
	glEnd();


	glutSwapBuffers();
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
