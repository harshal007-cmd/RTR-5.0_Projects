#include<GL\freeglut.h>
#include<math.h>
int bIsScreenFull = false;

static GLfloat t = 0.0f;
GLubyte fly[] = {
	 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	 0x03, 0x80, 0x01, 0xC0, 0x06, 0xC0, 0x03, 0x60,
	 0x04, 0x60, 0x06, 0x20, 0x04, 0x30, 0x0C, 0x20,
	 0x04, 0x18, 0x18, 0x20, 0x04, 0x0C, 0x30, 0x20,
	 0x04, 0x06, 0x60, 0x20, 0x44, 0x03, 0xC0, 0x22,
	 0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
	 0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
	 0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
	 0x66, 0x01, 0x80, 0x66, 0x33, 0x01, 0x80, 0xCC,
	 0x19, 0x81, 0x81, 0x98, 0x0C, 0xC1, 0x83, 0x30,
	 0x07, 0xe1, 0x87, 0xe0, 0x03, 0x3f, 0xfc, 0xc0,
	 0x03, 0x31, 0x8c, 0xc0, 0x03, 0x33, 0xcc, 0xc0,
	 0x06, 0x64, 0x26, 0x60, 0x0c, 0xcc, 0x33, 0x30,
	 0x18, 0xcc, 0x33, 0x18, 0x10, 0xc4, 0x23, 0x08,
	 0x10, 0x63, 0xC6, 0x08, 0x10, 0x30, 0x0c, 0x08,
	 0x10, 0x18, 0x18, 0x08, 0x10, 0x00, 0x00, 0x08 };


void borderPoly()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
	glEnd();

	glPolygonMode(GL_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glEdgeFlag(GL_TRUE);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
	glEdgeFlag(GL_FALSE);
	glEnd();

}

void PolyMode()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(0.5, -0.5, 0.0);

	glEnd();
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	borderPoly();
	//PolyMode();

	glutSwapBuffers();
}

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
